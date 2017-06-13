// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/log.h"
#include "foundation/task.h"
#include "foundation/task_set.h"
#include <algorithm>
#include <cassert>
#include <condition_variable>
#include <memory>
#include <mutex>

namespace gs {

/*!
	@short Task system

	Thread pool task system with task priority and worker affinity.
	Supports task dependencies.
*/
class task_system {
public:
	friend struct worker;

	~task_system();

	bool create_workers(uint count = 0);
	void delete_workers();

	inline uint get_worker_count() const { return worker_count; }
	inline std::thread::id get_worker_thread_id(uint index) const { return workers[index].get_id(); }

	/*!
		@short Push a new task to be executed by a worker.

		Tasks can be queued for execution after a task set has finished running.

		The task affinity controls on which worker to run the task and its
		priority controls the task insertion position in the worker queue.
		Higher priority tasks run before lower priority tasks.
	*/
	void push(const stask &t, task_affinity aff = any_task_worker, task_priority prt = default_task_priority) {
		setup_task(t, aff, prt);
		submit_task(t);
	}

	void push(const stask &t, const stask_set &set, task_affinity aff = any_task_worker, task_priority prt = default_task_priority) {
		setup_task(t, set, aff, prt);
		submit_task(t);
	}

	/// Queue a task for execution once a given task completes, the queued task belongs to its ancestor set.
	void queue(const stask &t, const stask &ancestor, task_affinity aff = any_task_worker, task_priority prt = default_task_priority) {
		{
			std::lock_guard<std::mutex> guard(lock);
			if (is_task_queued_or_running(ancestor)) { // queue for execution when ancestor completes...
				tasks_queued_on_task.emplace_back(ancestor, aff, prt, t);
				return;
			}
		}

		// ancestor has completed already, push task
		push(t, ancestor->set, aff, prt);
	}

	/// Push a task for execution once a given task set completes.
	void queue(const stask &t, const stask_set &ancestor, task_affinity aff = any_task_worker, task_priority prt = default_task_priority) {
		{
			std::lock_guard<std::mutex> guard(lock);
			if (is_task_set_open(ancestor)) { // queue for execution when ancestor completes...
				tasks_queued_on_set.emplace_back(ancestor, nullptr, aff, prt, t);
				return;
			}
		}
		push(t, aff, prt); // ancestor has completed execution already, push task
	}

	void queue(const stask &t, const stask_set &ancestor, const stask_set &set, task_affinity aff = any_task_worker, task_priority prt = default_task_priority) {
		{
			std::lock_guard<std::mutex> guard(lock);
			if (is_task_set_open(ancestor)) { // queue for execution when ancestor completes...
				tasks_queued_on_set.emplace_back(ancestor, set, aff, prt, t);
				return;
			}
		}
		push(t, set, aff, prt); // ancestor has completed execution already, push task
	}

	/// Wait for a task set to complete.
	void wait(const stask_set &set) {
		std::unique_lock<std::mutex> guard(lock);
		while (is_task_set_open(set))
			if (!steal_and_run_task(&set))
				task_complete_cv.wait(guard);
	}

	/// Keep a set open as long as another set is open.
	void set_keep_set_open(const stask_set &set, const stask_set &set_to_keep_open) {
		std::lock_guard<std::mutex> guard(lock);
		task_set_increase_count(set_to_keep_open);
		sets_kept_open_by_set.emplace_back(set_to_keep_open, set);
	}

	/*!
		@short Wait for a task to complete.
		@note The task must have been queued on the system, waiting on a task
		queued on another task is not supported at the moment.
	*/
	void wait(const stask &t) {
		std::unique_lock<std::mutex> guard(lock);
		while (is_task_queued_or_running(t))
			if (!steal_and_run_task(nullptr))
				task_complete_cv.wait(guard);
	}

	/// Wait for all tasks to complete.
	void wait_all_tasks() {
		std::unique_lock<std::mutex> guard(lock);
		while (get_task_left() > 0)
			if (!steal_and_run_task(nullptr))
				task_complete_cv.wait(guard);
	}

	/// Must be called before first pushing tasks related to a task set to the system.
	void begin_push_set_tasks(const stask_set &set) {
		std::lock_guard<std::mutex> guard(lock);
		task_set_increase_count(set);
	}

	/// Must be called after tasks related to a task set have been pushed to the system.
	void end_push_set_tasks(const stask_set &set) {
		std::lock_guard<std::mutex> guard(lock);
		task_set_decrease_count(set);
	}

	/// Return the number of task queued on a specific worker.
	uint get_worker_task_count(uint id) {
		std::lock_guard<std::mutex> guard(lock);
		return id < worker_count ? workers[id].get_task_queued() : 0;
	}

private:
	std::mutex lock;
	std::condition_variable task_queued_cv, task_complete_cv;

	std::vector<stask> queued_tasks, running_tasks;
	std::vector<stask_set> open_task_sets;

	struct task_queued_on_set {
		task_queued_on_set(stask_set ancestor_, stask_set set_, task_affinity aff_, task_priority prt_, stask tsk_) : ancestor(std::move(ancestor_)), set(std::move(set_)), aff(aff_), prt(prt_), tsk(std::move(tsk_)) {}

		stask_set ancestor;
		stask_set set;
		task_affinity aff;
		task_priority prt;
		stask tsk;
	};

	std::vector<task_queued_on_set> tasks_queued_on_set;

	inline bool is_task_queued_on_set(const stask &t) const {
		return std::find_if(tasks_queued_on_set.begin(), tasks_queued_on_set.end(), [&t](const task_queued_on_set &q) { return q.tsk == t; }) !=
			   tasks_queued_on_set.end();
	}

	inline bool is_task_set_open(const stask_set &set) const { return std::find(open_task_sets.begin(), open_task_sets.end(), set) != open_task_sets.end(); }

	struct task_queued_on_task {
		task_queued_on_task(stask ancestor_, task_affinity aff_, task_priority prt_, stask tsk_) : ancestor(std::move(ancestor_)), aff(aff_), prt(prt_), tsk(std::move(tsk_)) {}

		stask ancestor;
		task_affinity aff = any_task_worker;
		task_priority prt = default_task_priority;
		stask tsk;
	};

	std::vector<task_queued_on_task> tasks_queued_on_task;

	inline bool is_task_queued_on_task(const stask &t) const {
		return std::find_if(tasks_queued_on_task.begin(), tasks_queued_on_task.end(), [&t](const task_queued_on_task &q) { return q.tsk == t; }) !=
			   tasks_queued_on_task.end();
	}

	bool is_task_queued_or_running(const stask &t) const {
		// look in the system queued and running task lists
		if (std::find(queued_tasks.begin(), queued_tasks.end(), t) != queued_tasks.end() ||
			std::find(running_tasks.begin(), running_tasks.end(), t) != running_tasks.end() ||
			is_task_queued_on_task(t) || is_task_queued_on_set(t))
			return true;

		// look in each worker queue
		for (std::vector<worker>::size_type n = 0; n < worker_count; ++n)
			if (workers[n].is_task_queued(t))
				return true;

		return false;
	}

	struct set_kept_open_by_set {
		set_kept_open_by_set(const stask_set &k, const stask_set &b) : kept_open(k), by(b) {}
		stask_set kept_open, by;
	};

	std::vector<set_kept_open_by_set> sets_kept_open_by_set;

	uint get_task_left() const {
		uint count = queued_tasks.size() + running_tasks.size() + tasks_queued_on_set.size() + tasks_queued_on_task.size();
		for (uint n = 0; n < worker_count; ++n)
			count += workers[n].get_task_queued();
		return count;
	}

	void task_set_increase_count(const stask_set &set) {
		// open task set
		if (!is_task_set_open(set))
			open_task_sets.push_back(set); // shared_list, will keep the set alive

		++set->count; // increase task counter
	}

	void task_set_decrease_count(const stask_set &set) {
		if (--set->count == 0) {
			// gather tasks queued on this set...
			std::vector<task_queued_on_set> task_q;

			for (auto i = tasks_queued_on_set.begin(); i != tasks_queued_on_set.end();) {
				auto &q = *i;

				if (q.ancestor == set) {
					task_q.emplace_back(std::move(q));
					i = tasks_queued_on_set.erase(i);
				} else {
					++i;
				}
			}

			// ...and push them with no system lock held
			lock.unlock();

			for (auto &q : task_q)
				push(q.tsk, q.set, q.aff, q.prt);
			task_q.clear();

			lock.lock();

			// close sets kept open by this set
			stask_set sets_to_close[4];
			uint sets_to_close_count = 0;

			for (auto i = sets_kept_open_by_set.begin(); i != sets_kept_open_by_set.end();) {
				auto &o = *i;

				if (o.by == set) {
					/*
						note: a closing set might modify sets_opened_by_set
						while we are iterating on it if we were to call
						task_set_decrease_count from here
					*/
					__ASSERT__(sets_to_close_count < 4);
					sets_to_close[sets_to_close_count++] = o.kept_open;
					i = sets_kept_open_by_set.erase(i);
				} else {
					++i;
				}
			}

			for (uint i = 0; i < sets_to_close_count; ++i)
				task_set_decrease_count(sets_to_close[i]);

			// remove set from the open set list
			open_task_sets.erase(std::find(open_task_sets.begin(), open_task_sets.end(), set));
		}
	}

	inline void run_task(const stask &t) {
		t->run();

		{
			lock.lock();

			running_tasks.erase(std::find(running_tasks.begin(), running_tasks.end(), t)); // task done

			// gather tasks queued on this task...
			std::vector<task_queued_on_task> task_q;

			for (auto i = tasks_queued_on_task.begin(); i != tasks_queued_on_task.end();) {
				auto &q = *i;

				if (q.ancestor == t) {
					task_q.emplace_back(std::move(q));
					i = tasks_queued_on_task.erase(i);
				} else {
					++i;
				}
			}

			// ...and push them with no system lock held
			lock.unlock();

			for (auto &q : task_q)
				push(q.tsk, t->set, q.aff, q.prt); // push queued tasks on the same set as the task used
			task_q.clear();

			lock.lock();

			// decrease task set
			if (t->set)
				task_set_decrease_count(t->set);

			lock.unlock();
		}

		task_complete_cv.notify_all();
	}

	struct worker {
		enum State { run_state_stopped, run_state_running, run_state_shutdown };

		worker() : index(0), system(nullptr), run_state(run_state_stopped) { queued_tasks.reserve(16); }

		void set_name();

		inline bool is_task_queued(const stask &t) const {
			std::lock_guard<std::mutex> guard(lock);
			return find(queued_tasks.begin(), queued_tasks.end(), t) != queued_tasks.end();
		}

		inline uint get_task_queued() const {
			std::lock_guard<std::mutex> guard(lock);
			return queued_tasks.size();
		}

		stask pop() {
			// wait until a task is queued
			std::unique_lock<std::mutex> system_queue_guard(system->lock);
			while (system->queued_tasks.empty() && queued_tasks.empty() && run_state == run_state_running)
				system->task_queued_cv.wait(system_queue_guard);

			// fetch from local queue
			{
				std::lock_guard<std::mutex> local_queue_guard(lock);
				if (!queued_tasks.empty()) {
					auto t(std::move(queued_tasks.front()));
					queued_tasks.erase(queued_tasks.begin());
					system->running_tasks.push_back(t);
					return t;
				}
			}

			// fetch from global queue
			if (!system->queued_tasks.empty()) {
				auto t(std::move(system->queued_tasks.front()));
				system->queued_tasks.erase(system->queued_tasks.begin());
				system->running_tasks.push_back(t);
				return t;
			}

			return nullptr; // happens at shutdown
		}

		void execute() {
			set_name();
			for (run_state = run_state_running; true;)
				if (auto t = pop())
					system->run_task(t);
				else if (run_state != run_state_running)
					break; // exit once all tasks are run
			run_state = run_state_stopped;
		}

		void start() { thread = std::thread(&worker::execute, this); }
		void join() { thread.join(); }

		std::thread::id get_id() const { return thread.get_id(); }

		int index;

		task_system *system;

		std::thread thread;
		std::atomic<State> run_state;

		mutable std::mutex lock;
		std::vector<stask> queued_tasks;
	};

	uint worker_count = 0;
	std::unique_ptr<worker[]> workers;

	inline void insert_task_by_priority(std::vector<stask> &out_tasks, const stask &t) {
		std::lock_guard<std::mutex> guard(lock);

		auto i = out_tasks.end(), begin = out_tasks.begin();

		while (i != begin) {
			--i;
			if ((*i)->prt >= t->prt) {
				++i;
				out_tasks.insert(i, t);
				return;
			}
		}

		out_tasks.insert(out_tasks.begin(), t); // queue is full of lower priority tasks
	}

	void run_task_on_current_thread(const stask &t) {
		{
			std::lock_guard<std::mutex> guard(lock);
			running_tasks.push_back(t);
		}
		run_task(t);
	}

	// must be called with the system lock held
	bool steal_and_run_task(const stask_set *set) {
		stask t;

		{
			// try to steal from the system queue...
			if (queued_tasks.empty())
				return false;

			// ...a task belonging to a specific set...
			if (set)
				for (auto i = queued_tasks.begin(); i != queued_tasks.end(); ++i)
					if ((*i)->get_task_set() == *set) {
						t = *i;
						i = queued_tasks.erase(i);
						break;
					}

			// ...or a global one
			if (t == nullptr) {
				t = queued_tasks.front();
				queued_tasks.erase(queued_tasks.begin());
			}

			running_tasks.push_back(t);
		}

		lock.unlock();
		run_task(t);
		lock.lock();

		return true;
	}

	void push_task(const stask &t) {
		if (t->aff == any_task_worker) {
			insert_task_by_priority(queued_tasks, t);
			task_queued_cv.notify_one();
		} else {
			// If the task is being pushed from the worker thread it is supposed
			// to be executed by then execute it on the fly. Otherwise a wait on
			// the task future result could DEADLOCK the caller.
			//
			// FIXME this breaks the contract regarding task execution order.
			// This could be fixed by executing all queued tasks then this one.
			if (workers[t->aff].get_id() == std::this_thread::get_id()) {
				run_task_on_current_thread(t);
			} else {
				insert_task_by_priority(workers[t->aff].queued_tasks, t);
				task_queued_cv.notify_all(); // TODO only notify the correct worker, a full wake up is wasteful
			}
		}
	}

	void submit_task(const stask &t) {
		if (!worker_count) {
			run_task_on_current_thread(t);
		} else {
			if (workers[0].run_state == worker::run_state_running) // workers running
				push_task(t);
			else
				static_assert(true, "cannot run task");
		}
	}

	inline void setup_task(const stask &t, task_affinity aff, task_priority prt) {
		// assert affinity
		if (worker_count)
			if (aff != any_task_worker && uint(aff) >= worker_count)
				aff = task_affinity(worker_count - 1);

		// setup task
		t->aff = aff;
		t->prt = prt;
	}

	inline void setup_task(const stask &t, const stask_set &set, task_affinity aff, task_priority prt) {
		setup_task(t, aff, prt);

		if ((t->set = set)) {
			std::lock_guard<std::mutex> guard(lock);
			task_set_increase_count(set);
		}
	}
};

extern global_object<task_system> g_task_system;

} // gs
