// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/time.h"
#include <atomic>
#include <functional>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace gs {

class timer_thread {
public:
	typedef int handle;

	static const handle null_handle;

	enum State { Stopped, Running };

	explicit timer_thread(const char *name_ = "Timer") : name(name_) {}
	~timer_thread();

	/// Push a periodic call, the first call is done immediately.
	handle run_periodic(const std::function<void()> &call, time_t period, time_t initial_delay = 0);
	/// Push a delayed call.
	void run_delayed(const std::function<void()> &call, time_t delay);

	/// Cancel a periodic call.
	void cancel_periodic(handle);

	/// Start the timer thread, specifying the minimum timer resolution.
	void start(time_t resolution = time_from_ms(1));
	/// Stop the timer thread.
	void stop();

	bool is_running() const { return state != Stopped; }

	void execute();

private:
	std::string name;
	std::thread thread_;

	std::atomic<State> state{Stopped};
	std::mutex lock;

	time_t resolution = time_from_ms(1);

	struct delayed_call {
		delayed_call(const std::function<void()> &c, time_t d) : call(c), delay(d) {}
		std::function<void()> call;
		time_t delay;
	};

	struct periodic_call {
		periodic_call(const std::function<void()> &c, time_t p, time_t d) : call(c), period(p), delay(d) {}
		std::function<void()> call;
		time_t period, delay;
	};

	std::vector<delayed_call> delayed_calls;
	std::vector<periodic_call> periodic_calls;
};

extern global_object<timer_thread> g_timer_thread;

} // gs
