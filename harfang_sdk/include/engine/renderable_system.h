// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/immediate_renderable.h"
#include "engine/render_pass.h"
#include "engine/render_system.h"
#include "engine/octree_renderable.h"
#include "engine/scene_system.h"
#include "engine/simple_list_renderable.h"

namespace gs {
namespace core {

struct IFrameRenderer;
struct DefaultFrameRenderer;

class Environment;

/// Renderable system
class RenderableSystem : public std::enable_shared_from_this<RenderableSystem>, public SceneSystem {
public:
	struct RenderEnvironment {
		sNode camera;
		std::shared_ptr<LightSystem> light_system;
		std::shared_ptr<Environment> environment;
	};

	RenderableSystem(render::sRenderSystem, bool async = true);

	const std::string &GetAspect() const override;

	void AddComponent(sComponent component) override;
	void RemoveComponent(const sComponent &component) override;

	void Update(time_t dt) override;
	void Commit() override;

	/// Can be run from any thread, the render task is added to the update task set.
	void Render(sNode camera);

	/*!
		@short Render the complete system for picking.
		@note Must be run from the renderer thread.
	*/
	bool RenderPicking(const gpu::sRenderTarget &fbo);

	/// Force rendering of a single render pass shader for debugging purpose.
	void SetDebugRenderPassShader(render::RenderPass::Shader shader = render::RenderPass::ShaderCount);

	/// Set the system frame renderer.
	void SetFrameRenderer(std::shared_ptr<IFrameRenderer> renderer);

	/// Add a renderable to the system.
	void AddRenderable(render::sIRenderable r) { commit_queue.queue<void>(std::bind(&RenderableSystem::commit_AddRenderable, this, r)); }
	/// Remove a renderable from the system.
	void RemoveRenderable(const render::sIRenderable &r) { commit_queue.queue<void>(std::bind(&RenderableSystem::commit_RemoveRenderable, this, r)); }

	void DrawBuffers(uint idx_count, gpu::sBuffer idx, gpu::sBuffer vtx, const core::VertexLayout &vtx_layout, render::sMaterial mat, const MinMax &minmax, const Matrix4 &world, core::IndexType idx_type = core::IndexUShort, gpu::PrimitiveType prim_type = gpu::PrimitiveTriangle);
	void DrawGeometry(render::sGeometry geo, const Matrix4 &world);

	RenderEnvironment render_env;

	Signal<void(render::RenderSystem &)> pre_render_frame_signal;
	Signal<void(render::RenderSystem &)> post_render_frame_signal;

	void DrawDebugPanel(render::RenderSystem &render_system) override;
	void DrawDebugVisuals(render::RenderSystem &render_system) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

private:
	render::sRenderSystem render_system;

	std::shared_ptr<SimpleCullingSystem> simple_culling_system;
	std::shared_ptr<OctreeRenderable> octree_culling_system;

	std::shared_ptr<render::ImmediateRenderable> immediate_renderables[2]; // for immediate draw calls
	uint current_immediate_renderables; // ping-pong between updates

	render::IRenderableList renderables; // the system static root renderable list

	std::shared_ptr<DefaultFrameRenderer> default_frame_renderer;
	std::shared_ptr<IFrameRenderer> frame_renderer;

	void UpdateTask(const RenderEnvironment &env);

	bool is_async;
	std::future<void> show_frame_future;

	void Render_async(const RenderEnvironment &env);

	void commit_AddRenderable(const render::sIRenderable &);
	void commit_RemoveRenderable(const render::sIRenderable &);

	void commit_DrawBuffers(uint idx_count, gpu::sBuffer idx, gpu::sBuffer vtx, const core::VertexLayout &vtx_layout, render::sMaterial mat, const MinMax &local_minmax, const Matrix4 &world, core::IndexType idx_type, gpu::PrimitiveType prim_type);
	void commit_DrawGeometry(render::sGeometry geo, const Matrix4 &world);

	RenderEnvironment current_render_env;

	bool enable_immediate_rendering;

	bool dbg_draw_simple_culling_system = false;
	bool dbg_draw_octree_culling_system = false;
};

/// Frame renderer interface
struct IFrameRenderer {
	virtual ~IFrameRenderer() {}
	/// Initialize the frame renderer.
	virtual bool Initialize(render::RenderSystem &render_system) = 0;
	/// Render a frame.
	virtual void RenderFrame(render::RenderSystem &render_system, LightSystem &light_system, render::IRenderableList &renderables, const std::vector<core::sComponent> &post_processes) = 0;
	/// Shutdown the frame renderer.
	virtual void Shutdown(render::RenderSystem &render_system) = 0;
};

typedef std::shared_ptr<IFrameRenderer> sIFrameRenderer;

/// Default frame renderer
struct DefaultFrameRenderer : IFrameRenderer {
	DefaultFrameRenderer() : dbg_render_pass_shader(render::RenderPass::ShaderCount) {}

	bool Initialize(render::RenderSystem &render_system) override { return true; }
	void RenderFrame(render::RenderSystem &render_system, LightSystem &light_system, render::IRenderableList &renderables, const std::vector<core::sComponent> &post_processes) override;
	void Shutdown(render::RenderSystem &render_system) override {}

	render::RenderPass::Shader dbg_render_pass_shader;
};

} // core
} // gs
