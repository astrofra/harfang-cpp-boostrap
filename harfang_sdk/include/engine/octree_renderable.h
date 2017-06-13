// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderable.h"
#include <memory>
#include <vector>

namespace gs {
namespace render { class RenderSystem; }
namespace core {

/// Octree renderable
class OctreeRenderable : public render::IRenderable {
public:
	void AddRenderable(render::sIRenderable renderable);
	void DeleteRenderable(const render::sIRenderable &renderable);

	bool Update();

	/// Compute renderable world bounding box.
	MinMax GetWorldMinMax() const override;
	/// Cull system.
	Visibility Cull(const FrustumPlanes &frustum) override { return Inside; }
	/// Fill render primitive lists.
	void GetRenderPrimitives(const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, render::PrimitiveLists &primitive_lists, Context ctx) override;

	/// Set the maximum distance.
	void SetMaxDistance(float d = 0.f) { max_dist = d; }

	uint GetRenderableCount() const { return renderables.size(); }

	void DrawDebugVisuals(render::RenderSystem &render_system);

private:
	struct CachedNode {
		render::sIRenderable renderable;
		MinMax minmax;
	};

	struct OctreeNode {
		MinMax minmax;
		std::vector<CachedNode *> cached_node;
		std::unique_ptr<OctreeNode> child[2];
	};

	bool dirty = true;
	float max_dist = 0.f;

	std::vector<CachedNode> cached_nodes;
	std::unique_ptr<OctreeNode> root;

	render::IRenderableList renderables;

	OctreeNode *InsertList(std::vector<CachedNode *> &list);

	void GetNodeRenderPrimitives(OctreeNode *node, const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, render::PrimitiveLists &primitive_lists, Context ctx);
	void CullNodeRenderPrimitives(OctreeNode *node, const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, render::PrimitiveLists &primitive_lists, Context ctx);

	void DrawNodeDebugVisuals(render::RenderSystem &render_system, const OctreeNode *octree_node, uint depth, std::vector<MinMax> &node_minmax, std::vector<MinMax> &leaf_minmax);
};

} // core
} // gs
