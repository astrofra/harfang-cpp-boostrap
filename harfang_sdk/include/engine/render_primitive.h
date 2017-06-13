// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/display_list.h"
#include "engine/skeleton.h"

namespace gs {
namespace render {

struct PrimitiveLists;

struct RenderPrimitive {
	RenderPrimitive(uint idx_count_, core::IndexType idx_type_, gpu::PrimitiveType prim_type_, gpu::sBuffer idx_, gpu::sBuffer vtx_,
					const core::VertexLayout &vtx_layout_, const Matrix4 &world_, const MinMax &world_minmax_, core::sSkeleton skeleton_, sMaterial material_,
					uint32_t picking_id_)
		: idx_count(idx_count_), idx_type(idx_type_), prim_type(prim_type_), idx(std::move(idx_)), vtx(std::move(vtx_)), vtx_layout(vtx_layout_), world(world_),
		  world_minmax(world_minmax_), skeleton(skeleton_), material(std::move(material_)), picking_id(picking_id_) {}

	RenderPrimitive(uint idx_count_, core::IndexType idx_type_, gpu::PrimitiveType prim_type_, gpu::sBuffer idx_, gpu::sBuffer vtx_,
					const core::VertexLayout &vtx_layout_, const Matrix4 &world_, const MinMax &world_minmax_, sMaterial material_, uint32_t picking_id_)
		: idx_count(idx_count_), idx_type(idx_type_), prim_type(prim_type_), idx(std::move(idx_)), vtx(std::move(vtx_)), vtx_layout(vtx_layout_), world(world_),
		  world_minmax(world_minmax_), material(std::move(material_)), picking_id(picking_id_) {}

	uint32_t idx_count;
	core::IndexType idx_type;

	gpu::PrimitiveType prim_type;

	gpu::sBuffer idx;
	gpu::sBuffer vtx;
	core::VertexLayout vtx_layout;

	Matrix4 world;
	MinMax world_minmax;

	core::sSkeleton skeleton;

	sMaterial material;
	uint32_t picking_id;
};

class StateCache;

//
struct CustomPrimitive {
	virtual ~CustomPrimitive() {}

	/// Draw custom primitive.
	virtual void Draw(RenderSystem &render_system, StateCache &state_cache, const RenderPass &pass) = 0;
	/// Return the primitive world minmax.
	virtual MinMax GetWorldMinMax() const = 0;
};

typedef std::shared_ptr<CustomPrimitive> sCustomPrimitive;

//
struct PrimitiveLists {
	/// Return the number of primitive for a given pass.
	inline uint Size(RenderPass::Pass pass) const { return prims[pass].size() + customs[pass].size(); }
	/// Clear all primitive lists.
	void Clear();

	std::vector<RenderPrimitive> prims[RenderPass::PassCount];
	std::vector<std::shared_ptr<CustomPrimitive>> customs[RenderPass::PassCount];
};

void DrawPrimitives(RenderSystem &render_system, const PrimitiveLists &prim_lists, const RenderPass &pass);

} // render
} // gs
