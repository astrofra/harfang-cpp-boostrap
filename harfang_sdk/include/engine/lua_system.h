// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/script_system.h"

namespace gs {
namespace script {

class LuaVM;

//
class LuaSystem : public core::ScriptSystem {
public:
	typedef uint8_t VMIndex; // max 256 VM context type

	struct ContextDesc { // 2 bytes
		enum Type : uint8_t { Logic, Render };

		ContextDesc() : type(Logic), index(0) {}
		ContextDesc(Type t, uint8_t i) : type(t), index(i) {}

		Type type;
		VMIndex index; // VM index
	};

	struct InitPending {
		enum Type : uint8_t { Uninit, Init };

		InitPending() : init(Init), index(0) {}
		InitPending(core::sScript s_, Type i_, VMIndex v_) : s(std::move(s_)), init(i_), index(v_) {}

		core::sScript s;

		Type init;
		VMIndex index;
	};

	struct Context {
		Context();
		~Context();

		std::shared_ptr<LuaVM> vm;

		std::vector<ParameterChangeNotification> queued_parameter_change_notifications;

		bool Open();
		void Close();

		std::vector<InitPending> init_pending;

		bool debug;
	};

	struct Statistics {
		time_t update = 0, garbage_collect = 0;
	};

	explicit LuaSystem(core::sScriptEngineEnv env = nullptr);
	~LuaSystem();

	const std::string &GetImplementationName() const override;

	void AddComponent(core::sComponent component) override;
	void RemoveComponent(const core::sComponent &component) override;

	void Update(time_t dt) override;
	void Commit() override;

	bool Open() override;
	void Close() override;
	void Reset() override;

	bool IsOpen() const;
	void OnRuntimeError(const RuntimeError &error);

	sVM GetVM(const core::Script &component) override;

	void SetMouseEvent(core::MouseEvent event) override { mouse_event = event; };

	inline Context *GetContext(ContextDesc desc) { return desc.type == ContextDesc::Render ? &render_ctx : &logic_ctx[desc.index]; }
	Context *GetContext(const VM &vm);

	void DrawDebugPanel(render::RenderSystem &render_system) override;

private:
	std::map<const core::Script *, ContextDesc> script_context_map;

	bool InitializeScriptCommon(Context &ctx, const core::sScript &s, ContextDesc desc);
	bool UninitializeScriptCommon(Context &ctx, const core::sScript &s);

	void ProcessParameterChangeNotifications(Context &ctx);

	std::vector<InitPending> logic_init_pending;

	//-----
	uint8_t logic_ctx_assign;
	std::vector<Context> logic_ctx;
	std::vector<LogicDlgts> logic_dlgt;
	std::vector<Statistics> logic_stat;

	Object S_; // table shared by all components running on the master logic VM

	void ProcessLogicPendingInit(std::vector<InitPending> &init);
	void UpdateLogicContext(uint idx);

	void RemoveScriptDelegates(Context &ctx, core::Script &script_component);

	//-----
	core::MouseEvent mouse_event;

	//-----
	Context render_ctx; // rendering context
	Statistics render_stat;

	void commit_NotifyParameterChange(core::sScript script, const char *name) override;

	//-----
	void ProcessLogicInit();
	void RunGarbageCollection(Context &ctx, Statistics &stats);

	//-----
	void ProcessRenderContextInit(LuaSystem::Context &ctx);

	void OnRenderSystemBeginDrawFrame(render::RenderSystem &render_system) override;
	bool OnRenderSystemClearFrame(render::RenderSystem &render_system) override;
	void OnRenderSystemFrameComplete(render::RenderSystem &render_system) override;
	void OnRenderSystemEndRenderPass(render::RenderSystem &render_system, render::RenderPass::Pass pass) override;

	bool OnRenderSystemApplyPostProcesses(render::RenderSystem &render_system, const gpu::sRenderTarget &rt, const gpu::sTexture &src, const gpu::sTexture &dst) override;

	std::map<core::Script *, script::Object> begin_draw_frame_dlgt, clear_frame_dlgt, end_draw_dlgt, end_render_pass_dlgt, post_process_dlgt;

	void AddRenderDelegates(LuaVM &vm, core::Script &s);
	void RemoveRenderDelegates(core::Script &s);

	//-----
	void DrawContextDebugPanel(const char *name, LuaSystem::Context &ctx);
};

} // script
} // gs
