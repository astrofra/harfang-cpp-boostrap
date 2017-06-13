// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "engine/script_execution_context.h"
#include "engine/script_object.h"
#include "foundation/reflection.h"

#undef Expose

namespace gs {
namespace core {

// A script parameter editable in the editor property panel.
struct ScriptParam {
	ScriptParam() = default;
	ScriptParam(const char *name_, const char *type_) : name(name_), type(type_) {}

	std::string name, type;
	TypeValue value;
};

typedef std::shared_ptr<ScriptParam> sScriptParam;

struct ScriptParamList : std::vector<sScriptParam> {}; // type used to specialize serialization code

// Used to store a (non parameter) value set before the component is setup.
struct ScriptSetValue {
	ScriptSetValue() = default;
	ScriptSetValue(const char *name_, const TypeValue &value_) : name(name_), value(value_) {}

	std::string name;
	TypeValue value;
};

/// Script component interface
class Script : public Component {
public:
	Script(const char *path = "");

	comp_decl_member_get_sync_set_async_noimpl(Script, std::string, Path, path)

		inline bool IsInitialized() const { return is_initialized; }

	ScriptParamList parameters;
	sScriptParam GetParam(const char *name) const;

	ComponentState GetState() const override;

	/// Directly retrieve a value from the component environment with a blocking call.
	TypeValue BlockingGet(const char *name) const;

	/// Get a value from the component exposed values.
	TypeValue Get(const char *name) const;
	/// Set a value in the component environment.
	void Set(const char *name, const TypeValue &value);

	/// Expose a named value.
	void Expose(const char *name, const TypeValue &value);

	void Call(const char *name, const std::vector<TypeValue> &parms);

	std::vector<ScriptSetValue> set_values;

	virtual script::Object GetEnv() { return env; }

	script::Object env;
	script::Object is_ready_fn; // IsReady script delegate

	script::sExecutionContext exec_ctx;

private:
	std::map<std::string, TypeValue> exposed_values;

	friend void ScriptSetIsInitialized(Script &script, bool is_initialized);
	friend void ScriptSetInternalComponentState(Script &script, ComponentState state);
	friend ComponentState ScriptGetInternalComponentState(const Script &script);

	bool is_initialized;
	ComponentState state;

	void commit_Set(const char *name, const TypeValue &value);
	void commit_Expose(const char *name, const TypeValue &value);
	void commit_Call(const char *name, const std::vector<TypeValue> &parms);
};

/// Logic script component interface
struct LogicScript : public std::enable_shared_from_this<LogicScript>, public Script {
	decl_component_defaults(LogicScript, "LogicScript");

	LogicScript(const char *path = "");

	comp_decl_member_get_sync_set_async_noimpl(LogicScript, bool, RunOnMasterVM, run_on_master_vm)

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

/// Render script component interface
struct RenderScript : public std::enable_shared_from_this<RenderScript>, public Script {
	decl_component_defaults(RenderScript, "RenderScript");

	RenderScript(const char *path = "");

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	script::Object begin_draw_frame, end_draw_frame;
};

typedef std::shared_ptr<Script> sScript;

} // core
} // gs
