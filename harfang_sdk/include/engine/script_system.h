// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/collision_pair.h"
#include "engine/mixer_async.h"
#include "engine/mouse_event.h"
#include "engine/render_system_async.h"
#include "engine/renderer_async.h"
#include "engine/scene_system.h"
#include "engine/script.h"
#include "engine/vm.h"
#include "foundation/signal.h"
#include "foundation/string.h"

namespace gs {
namespace gpu { class RendererAsync; }
namespace audio { class MixerAsync; }
namespace core {

struct ScriptComponentExecutionContext : script::ExecutionContext {
	ScriptComponentExecutionContext(sScript s) : script_component(s) {}

	std::string GetDescription() const override;
	script::Object GetEnv() const override;

private:
	sScript script_component;
};

/// Global engine environment shared by all scripts in the system.
struct ScriptEngineEnv {
	ScriptEngineEnv(render::sRenderSystemAsync s, gpu::sRendererAsync r, audio::sMixerAsync m) : render_system_async(s), renderer_async(r), mixer_async(m), dt(0) {}

	render::sRenderSystemAsync render_system_async;
	gpu::sRendererAsync renderer_async;
	audio::sMixerAsync mixer_async;

	float dt; // dt_clock for the current frame (in sec)
};

typedef std::shared_ptr<ScriptEngineEnv> sScriptEngineEnv;

namespace ScriptExecutionContext {
typedef uint Type;
static const Type Standalone = 0x01, Editor = 0x02, All = 0xff;
}

/// Script system interface
class ScriptSystem : public std::enable_shared_from_this<ScriptSystem>, public SceneSystem {
public:
	explicit ScriptSystem(sScriptEngineEnv engine_env = nullptr);
	~ScriptSystem();

	const std::string &GetAspect() const override;

	/// Return the script execution context.
	ScriptExecutionContext::Type GetExecutionContext() const { return execution_context; }
	/// Set the script execution context.
	void SetExecutionContext(ScriptExecutionContext::Type ctx) { execution_context = ctx; }

	/// Notify a script that a parameter value has been modified.
	void NotifyParameterChange(sScript script, const char *name);
	/// Return true if the script is ready (might imply a call to a script function).
	bool TestScriptIsReady(const Script &script);

	/// Get implementation name.
	virtual const std::string &GetImplementationName() const = 0;

	/// Open system.
	virtual bool Open() = 0;
	/// Close system.
	virtual void Close() = 0;

	/// Reset the system, destroy all object references from the system VM.
	virtual void Reset() = 0;

	/// Return the VM for a given script.
	virtual script::sVM GetVM(const Script &script) = 0;

	typedef Signal<void(const script::RuntimeError &)> RuntimeErrorSignal;
	RuntimeErrorSignal runtime_error_signal;

	void ConnectToRenderSystemSignals(render::RenderSystem &render_system);
	void DisconnectFromRenderSystemSignals(render::RenderSystem &render_system);

	virtual void SetMouseEvent(MouseEvent event) = 0;

	struct LogicDlgts {
		std::map<core::Script *, script::Object> update_dlgt, end_draw_dlgt, mouse_event_dlgt, on_collision_dlgt;
	};

	typedef Signal<void(script::VM &, const LogicDlgts &)> UpdateLogicContextSignal;
	UpdateLogicContextSignal update_logic_context_signal;

	/// Emitted right after a VM value has been changed, the VM lock is being held by the caller.
	Signal<void(const sScript &, const char *)> script_component_commit_set_signal;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

protected:
	Signal<void(const sScript &, const char *)>::Connection script_component_commit_set_connection;

	sScriptEngineEnv engine_env;
	ScriptExecutionContext::Type execution_context;

	struct ParameterChangeNotification {
		ParameterChangeNotification(sScript script, const char *name);
		~ParameterChangeNotification();

		sScript script;
		std::string name;
	};

	virtual void commit_NotifyParameterChange(core::sScript script, const char *name) = 0;

	void OnScriptComponentCommitSet(const core::sScript &script, const char *name);

	const std::vector<CollisionPair> *collision_pairs;

	virtual void OnRenderSystemBeginDrawFrame(render::RenderSystem &render_system) {}
	virtual bool OnRenderSystemClearFrame(render::RenderSystem &render_system) { return false; }
	virtual void OnRenderSystemFrameComplete(render::RenderSystem &render_system) {}
	virtual void OnRenderSystemEndRenderPass(render::RenderSystem &render_system, render::RenderPass::Pass pass) {}

	virtual bool OnRenderSystemApplyPostProcesses(render::RenderSystem &render_system, const gpu::sRenderTarget &rt, const gpu::sTexture &src, const gpu::sTexture &dst) { return false; }

	Signal<void(render::RenderSystem &)>::Connection begin_draw_frame_connection, frame_complete_connection;
	Signal<bool(render::RenderSystem &)>::Connection clear_frame_connection;
	Signal<void(render::RenderSystem &, render::RenderPass::Pass)>::Connection end_render_pass_connection;
	Signal<bool(render::RenderSystem &, const gpu::sRenderTarget &rt, const gpu::sTexture &src, const gpu::sTexture &dst)>::Connection apply_post_processes_connection;
};

} // core
} // gs
