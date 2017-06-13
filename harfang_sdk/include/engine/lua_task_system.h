// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#include "foundation/task_system.h"
#include "engine/lua_vm.h"

namespace gs {
namespace script {

class LuaTask
{
	friend class LuaTaskSystem;
protected:
	std::vector<Object> chunks; // the task chunk compiled on each system available logic VM
};

typedef std::shared_ptr<LuaTask> sLuaTask;

class LuaTaskHandle
{
	friend class LuaTaskSystem;
public:
	enum TaskState { TaskPending, TaskRunning, TaskComplete, TaskFailed };

	LuaTaskHandle() : state(TaskPending) {}

	/// Return the task state.
	TaskState GetState() const { return state; }
	/// Return true if the task is complete or failed.
	bool IsCompleteOrFailed() const { return state > 1; }

	/// Return an array of results from the task.
	const std::vector<TypeValue> &GetResults() const { return results; }

protected:
	std::atomic<TaskState> state;

	std::vector<TypeValue> results;
};

typedef std::shared_ptr<LuaTaskHandle> sLuaTaskHandle;

class LuaTaskSystem
{
public:
	bool Start(uint worker_count = 0);
	void Stop();

	sLuaTask PrepareTask(const char *source);
	sLuaTaskHandle RunTask(sLuaTask task, uint arg_count, const TypeValue *args);

	uint GetWorkerCount() const { return lua_vm.size(); }

private:
	void RunTaskParallel(std::shared_ptr<LuaTask> task, sLuaTaskHandle handle, const std::vector<TypeValue> &args);

	std::vector<sLuaVM> lua_vm;
	task_system lua_task_system;
};

} // script
} // gs
