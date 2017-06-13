// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "foundation/mixed_block_allocator.h"
#include "foundation/reflection.h"
#include "engine/vm.h"
#include <map>
#include <memory>

struct lua_State;
struct lua_Debug;

namespace gs {
namespace script {

class LuaObjectImpl : public Object::Impl {
public:
	explicit LuaObjectImpl(lua_State *L_);
	LuaObjectImpl(lua_State *L_, int _ref) : L(L_), ref(_ref) {}
	~LuaObjectImpl();

	void Clear();

	int Get() const { return ref; }
	void Set(int ref);

	bool IsValid() const override;
	bool IsNull() const override;

private:
	lua_State *L;
	int ref;
};

/*!
	Wrapper for the Lua VM.
	This class is not thread-safe.
*/
class LuaVM : public VM {
public:
	typedef MixedBlockAllocator<4> Allocator;

	LuaVM(const char *name = "") : VM(name), L(nullptr), exec_watchdog_last_update(0), exec_watchdog_timeout(1000) {}

	bool Open() override;
	void Close() override;
	bool IsOpen() const override;

	const char *GetInterpreter() const override;

	void InstallExecutionWatchdog(int timeout);

	lua_State *GetLuaState() const { return L; }

	/// Push an object on the Lua stack.
	bool Push(const Object &o);

	/// Compile a script to a chunk.
	bool Compile(const char *source, Object &chunk_out) override;
	/// Execute a script.
	bool Execute(const char *source, const char *name = nullptr, Object *env = nullptr, std::vector<Object> *ret_vals = nullptr, sExecutionContext exec_ctx = nullptr) override;

	Object CreateNull() override;
	Object CreateEnvironment() override;
	Object CreateTable() override;
	Object CreateArray() override;

	/// Retrieve a VM object.
	Object Get(const char *key, const Object *context = nullptr) override;
	bool Set(const char *key, const Object &val, const Object *context = nullptr) override;

	Object Get(int index, const Object &array_object) override;
	bool Set(int index, const Object &val, const Object &array_object) override;

	TypeValue ObjectToValue(const Object &, const char *cast_to = nullptr) override;
	Object ValueToObject(const TypeValue &) override;

	template <class T> T CastObject(const Object &o, T dflt, const char *cast_to = nullptr) {
		auto v = ObjectToValue(o, cast_to);
		return v.GetType() == g_type_registry.get().GetType<T>() ? v.Cast<T>() : dflt;
	}

	bool Call(const Object &func, uint nparm, const Object *parms, std::vector<Object> *ret_vals = nullptr, sExecutionContext exec_ctx = nullptr) override;

	void ResetExecutionWatchdog();

	/// Capture current execution callstack.
	void CaptureCallstack(Callstack &callstack);

private:
	friend void lua_watchdog_hook(lua_State *L, lua_Debug *ar);
	friend int lua_error_handler(lua_State *L);

	lua_State *L;
	Allocator allocator;

	bool GatherReturnValues(lua_State *L, int start_index, std::vector<Object> &ret_vals);

	time_t exec_watchdog_last_update, exec_watchdog_timeout;
};

typedef std::shared_ptr<LuaVM> sLuaVM;

sLuaVM LuaVMFromLuaState(lua_State *L);
sLuaVM MakeSharedLuaVM();

} // gs
} // script
