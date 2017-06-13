// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry.h"
#include "engine/material.h"

namespace gs {
namespace core {

struct GeometryTraceBase {
	Geometry *g;

	float i_t; ///< Distance to intersection from ray's origin.
	bool backface; ///< Hit is on the back face of the polygon.

	int ip; ///< Polygon index.
	uint it; ///< Triangle index in polygon.
	uint bi; ///< Polygon binding start index.
	float u, v, w; ///< Barycentric coordinates.

	Material *m;
};

// Raytrace result.
struct GeometryTrace : public GeometryTraceBase {
	explicit GeometryTrace(bool closest = true) : want_closest(closest), has_i(false), node_visited(0), tri_test(0) {}

	Vector3 s; ///< Ray origin.
	Vector3 d; ///< Ray direction.

	bool want_closest;
	bool has_i; ///< Do we have an intersection.

	uint node_visited; ///< Number of nodes visited.
	uint tri_test; ///< Number of triangle tested.
};

/// Geometry tree interface
class IGeometryTree {
public:
	virtual ~IGeometryTree() {}

	inline const sGeometry &GetGeometry() const { return geometry; }

	/*!
		@short Specify a fixed ray origin.

		This function provides the tree implementation with an optimization
		opportunity by specifying a fixed ray origin.

		@note Pass nullptr to remove hint.
	*/
	virtual void SetRayOriginHint(const Vector3 *) {}

	/// Raytrace the geometry tree.
	virtual void RaytraceGeometry(GeometryTrace &, const Vector3 &s, const Vector3 &d, float length = -1.f) = 0;
	/// Build tree from a geometry.
	virtual bool BuildFromGeometry(Geometry *) = 0;
	/// Free all internal structures.
	virtual void Free() = 0;

protected:
	sGeometry geometry;
};

} // core
} // gs
