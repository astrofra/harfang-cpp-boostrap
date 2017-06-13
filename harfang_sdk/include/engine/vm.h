// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/script_callstack.h"
#include "engine/script_execution_context.h"
#include "engine/script_object.h"
#include "engine/script_runtime_error.h"
#include "foundation/reflection.h"
#include "foundation/signal.h"
#include <memory>
#include <string>

namespace gs {
namespace script { struct Object;

class VM {
public:
	VM(const char *_name = "") : name(_name) {}

	std::string name;

	bool TryLock() { return vm_mutex.try_lock(); }
	void Lock() { vm_mutex.lock(); }
	void Unlock() { vm_mutex.unlock(); }

	/// Compile a script to a chunk.
	virtual bool Compile(const char *source, Object &chunk_out) = 0;
	/// Execute a source script.
	virtual bool Execute(const char *source, const char *name = nullptr, script::Object *env = nullptr, std::vector<Object> *ret_vals = nullptr, sExecutionContext exec_ctx = nullptr) = 0;

	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual bool IsOpen() const = 0;

	virtual const char *GetInterpreter() const { return "Undefined"; }

	virtual Object CreateNull() = 0;
	virtual Object CreateEnvironment() = 0;
	virtual Object CreateTable() = 0;
	virtual Object CreateArray() = 0;

	/// Retrieve a VM object.
	virtual TypeValue ObjectToValue(const Object &, const char *cast_to = nullptr) = 0;
	virtual Object ValueToObject(const TypeValue &) = 0;

	inline Object CreateObject(const TypeValue &v) { return ValueToObject(v); }

	virtual Object Get(const char *key, const Object *context = nullptr) = 0;
	virtual bool Set(const char *key, const Object &val, const Object *context = nullptr) = 0;

	virtual Object Get(int index, const Object &array_object) = 0;
	virtual bool Set(int index, const Object &val, const Object &array_object) = 0;

	TypeValue GetValue(const char *key, const Object *context = nullptr);
	bool SetValue(const char *key, const TypeValue &val, const Object *context = nullptr);

	TypeValue GetValue(int index, const Object &array_object);
	bool SetValue(int index, const TypeValue &val, const Object &array_object);

	void PushExecutionContext(sExecutionContext ctx) { exec_ctx_stack.emplace_back(std::move(ctx)); }
	void PopExecutionContext() { exec_ctx_stack.pop_back(); }

	sExecutionContext GetCurrentExecutionContext() const { return exec_ctx_stack.size() > 0 ? exec_ctx_stack.back() : nullptr; }

	/// Call into the VM.
	virtual bool Call(const Object &function, uint nparm, const Object *parms, std::vector<Object> *ret_vals = nullptr, sExecutionContext exec_ctx = nullptr) = 0;

	typedef Signal<void(const RuntimeError &)> RuntimeErrorSignal;

	RuntimeErrorSignal runtime_error_signal;
	bool emit_runtime_error_signal = true;

protected:
	std::mutex vm_mutex;
	std::vector<sExecutionContext> exec_ctx_stack;
};

extern Signal<void(VM *)> vm_open_signal, vm_close_signal;

//----
class VMLock {
public:
	VM &GetVM() const { return vm; }

	explicit VMLock(VM &v) : vm(v) { vm.Lock(); }
	~VMLock() { vm.Unlock(); }

private:
	VM &vm;
};

typedef std::shared_ptr<VM> sVM;

} // script
} // gs
