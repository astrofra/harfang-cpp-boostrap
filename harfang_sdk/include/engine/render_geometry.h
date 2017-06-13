// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry.h"
#include "engine/display_list.h"
#include "engine/renderable.h"
#include "engine/skeleton.h"

namespace gs {
namespace render {

class Geometry : public gpu::Resource {
public:
	explicit Geometry(const char *name = "");

	/// Change a material in the material table.
	bool SetMaterial(uint index, sMaterial mat);
	/// Re-create from core geometry.
	void Create(RenderSystem &render_system, const core::sGeometry &geo);
	/// Free geometry.
	void Free();

	bool IsReadyOrFailed() const override;

	std::vector<sMaterial> materials;

	core::GeometryFlag::Type flag;

	MinMax minmax; // local minmax

	std::shared_ptr<Geometry> lod_proxy;
	float lod_distance;

	std::shared_ptr<Geometry> shadow_proxy;

	std::vector<Matrix4> bone_bind_matrix;
	std::vector<MinMax> bone_minmax;
	std::vector<DisplayList> display_list;
};

typedef std::shared_ptr<Geometry> sGeometry;

bool SaveRenderGeometry(const Geometry &render_geo, core::Geometry &geo, const char *path = nullptr);

/// Return the geometry level of detail for a given render context.
sGeometry GetGeometryLod(sGeometry geo, const Matrix4 &geo_world, const Matrix4 &view_world, IRenderable::Context ctx);

/// Cull and add all of a geometry render primitives matching the current draw configuration.
void SubmitGeometryRenderPrimitives(const Geometry &geo, const Matrix4 &world, const Matrix4 &view_world, uint picking_id, PrimitiveLists &prim_lists, IRenderable::Context ctx);
void SubmitGeometryRenderPrimitives(const Geometry &geo, const Matrix4 &world, const Matrix4 &view_world, uint picking_id, const core::sSkeleton &skeleton, PrimitiveLists &prim_lists, IRenderable::Context ctx);

/// Create render geometry from core geometry.
void CoreGeometryToRenderGeometry(RenderSystem &render_system, const core::Geometry &geo, Geometry &out);

} // render
} // gs
