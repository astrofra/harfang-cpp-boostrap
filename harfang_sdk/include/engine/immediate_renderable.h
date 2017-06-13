// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderable.h"
#include "engine/render_primitive.h"
#include "engine/render_material.h"
#include "engine/render_geometry.h"
#include "engine/gpu_buffer.h"
#include "engine/vertex_layout.h"
#include "foundation/matrix4.h"

namespace gs {
namespace render {

struct DrawGeometryCommand {
	DrawGeometryCommand(sGeometry geo_, const Matrix4 &world_) : geo(geo_), world(world_) {}
	DrawGeometryCommand(DrawGeometryCommand &&c) : geo(std::move(c.geo)), world(std::move(c.world)) {}

	sGeometry geo;
	Matrix4 world;
};

struct ImmediateRenderable : IRenderable {
	void Reset();

	void AddDrawBuffersPrimitive(uint idx_count, gpu::sBuffer idx, gpu::sBuffer vtx, const core::VertexLayout &vtx_layout, sMaterial mat, const MinMax &local_minmax, const Matrix4 &world, core::IndexType idx_type = core::IndexUShort, gpu::PrimitiveType prim_type = gpu::PrimitiveTriangle);
	void AddDrawGeometryCommand(sGeometry geo, const Matrix4 &world);

	MinMax GetWorldMinMax() const override { return minmax; }
	Visibility Cull(const FrustumPlanes &frustum) override { return ClassifyMinMax(frustum, minmax); }
	void GetRenderPrimitives(const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, PrimitiveLists &primitive_lists, Context ctx) override;

	uint GetRenderPrimitiveCount() const { return render_primitives.size(); }
	uint GetDrawGeometryCommandCount() const { return draw_geometry_commands.size(); }

private:
	MinMax minmax;

	std::vector<RenderPrimitive> render_primitives; // immediate render primitives
	std::vector<DrawGeometryCommand> draw_geometry_commands;

	void GrowMinMax(const MinMax &mm);
};

} // render
} // gs
