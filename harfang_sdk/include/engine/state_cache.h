// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/render_pass.h"
#include "engine/vertex_layout.h"
#include "foundation/cext.h"
#include "foundation/matrix4.h"

namespace gs {
namespace core { struct Skeleton; }

namespace gpu {
struct Shader;
struct Buffer;
} // gpu

namespace render {

class Material;
class RenderSystem;

/// Cache to limit render system and renderer state changes.
class StateCache {
public:
	struct Stats {
		uint world_change;
		uint picking_id_change;
		uint skeleton_change;
		uint shader_change;
		uint material_change;
		uint index_buffer_change;
		uint vertex_buffer_change;
		uint vertex_layout_change;
		uint surface_draw_state_change;
		uint pass_change;
		uint light_change;
		uint commit_count;
	};

	StateCache();
	~StateCache();

	void Reset();

#define SetEntry(C, O, V) C = set_if_not_equal(O, V);

	inline void SetWorld(const Matrix4 &w) { SetEntry(world_change, world, w); }
	inline void SetPickingID(uint id) { SetEntry(picking_id_change, picking_id, id); }
	inline void SetSkeleton(std::shared_ptr<core::Skeleton> s) { SetEntry(skeleton_change, skeleton, s); }
	inline void SetShader(std::shared_ptr<gpu::Shader> s) { SetEntry(shader_change, shader, s); }
	inline void SetMaterial(std::shared_ptr<Material> m) { SetEntry(material_change, material, m); }
	inline void SetIndexBuffer(std::shared_ptr<gpu::Buffer> b) { SetEntry(index_buffer_change, idx, b); }
	inline void SetVertexBuffer(std::shared_ptr<gpu::Buffer> b) { SetEntry(vertex_buffer_change, vtx, b); }
	inline void SetVertexLayout(const core::VertexLayout &l) { SetEntry(vertex_layout_change, vtx_layout, l); }
	inline void SetSurfaceDrawState(uint state) { SetEntry(surface_draw_state_change, surface_draw_state, state); }
	inline void SetRenderPass(RenderPass::Pass p) { SetEntry(pass_change, pass, p); }
	inline void SetLight(core::sNode l) { SetEntry(light_change, light, l); }

	bool Commit(RenderSystem &render_system);

	void ResetStat();
	const Stats &GetStat() const { return stat; }

private:
	Stats stat;

	uint world_change : 1;
	uint picking_id_change : 1;
	uint skeleton_change : 1;
	uint shader_change : 1;
	uint material_change : 1;
	uint index_buffer_change : 1;
	uint vertex_buffer_change : 1;
	uint vertex_layout_change : 1;
	uint surface_draw_state_change : 1;
	uint pass_change : 1;
	uint light_change : 1;

	Matrix4 world;
	uint picking_id;
	std::shared_ptr<core::Skeleton> skeleton;
	std::shared_ptr<gpu::Shader> shader;
	uint surface_draw_state;
	std::shared_ptr<Material> material;
	std::shared_ptr<gpu::Buffer> idx;
	std::shared_ptr<gpu::Buffer> vtx;
	core::VertexLayout vtx_layout;
	RenderPass::Pass pass;
	std::shared_ptr<core::Node> light;
};

struct RasterFont;

} // render
} // gs
