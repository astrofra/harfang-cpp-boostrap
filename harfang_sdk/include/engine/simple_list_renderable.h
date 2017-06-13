// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderable.h"

namespace gs {
namespace core {

/// Simple list renderable
class SimpleCullingSystem : public render::IRenderable {
public:
	/// Add a renderable to the culling system.
	void AddRenderable(std::shared_ptr<render::IRenderable> renderable);
	/// Delete a renderable from the culling system.
	void DeleteRenderable(const std::shared_ptr<render::IRenderable> &renderable);

	/// Compute system world bounding box.
	MinMax GetWorldMinMax() const override;
	/// Cull system.
	Visibility Cull(const FrustumPlanes &frustum) override { return Inside; } // culling is done by GetRenderPrimitives
	/// Get renderable primitives.
	void GetRenderPrimitives(const FrustumPlanes &frustum, const Matrix4 &frustum_world_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, render::PrimitiveLists &primitive_lists, Context ctx) override;

	const render::IRenderableList &GetRenderables() const { return renderables; }
	uint GetRenderableCount() const { return renderables.size(); }

protected:
	render::IRenderableList renderables;
};

} // core
} // gs
