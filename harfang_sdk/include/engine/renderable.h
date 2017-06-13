// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>
#include <memory>

#include "foundation/minmax.h"
#include "foundation/frustum.h"
#include "foundation/matrix44.h"

namespace gs { struct FrustumPlanes;
namespace render {

struct PrimitiveLists;

/// Renderable interface
struct IRenderable {
	enum Context { ContextDefault = 0, ContextShadow };

	/// Get renderable world minmax.
	virtual MinMax GetWorldMinMax() const = 0;

	/// Cull renderable.
	virtual Visibility Cull(const FrustumPlanes &frustum) = 0;
	/// Get renderable primitives.
	virtual void GetRenderPrimitives(const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, PrimitiveLists &primitive_lists, Context ctx) = 0;
};

typedef std::shared_ptr<IRenderable> sIRenderable;
typedef std::vector<sIRenderable> IRenderableList;

} // render
} // gs
