// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry.h"
#include "engine/geometry_tree.h"
#include "engine/material.h"
#include "foundation/bih.h"

namespace gs {
namespace core {

/// BIH ray/triangle intersection acceleration structure.
struct GeometryBIHAccel {
	char cu, cv;
	std::vector<float> k;
	float d;
};

struct GeometryBIHMaterial {
	sMaterial material;
};

/*
	@short Geometry polygon bounding interval hierarchy

	Raytracing/intersection acceleration structure theoretically
	performing within 70% of the SAH/KD-Tree performances.
*/
class GeometryBIH : public IGeometryTree, public bih::Tree {
public:
	/// Return the raytracing LUT structure.
	const std::vector<GeometryBIHAccel> &GetRaytracingAccelerationStructure() const { return acc; }

	/// Fast polygon test.
	bool FastPolyTest(uint ip, Vector3 &s, Vector3 &d, float l = -1.f);

	void RaytraceGeometry(GeometryTrace &trace, const Vector3 &s, const Vector3 &d, float l = -1.f) override;
	bool BuildFromGeometry(Geometry *) override;
	void Free() override;

private:
	std::vector<GeometryBIHMaterial> material_table; ///< material table
	std::vector<uint> pol_index;

	std::vector<GeometryBIHAccel> acc; ///< raytracing lookup tables

	/// Trace leaf content.
	void TraceLeaf(bih::Node *leaf, float tmin, float tmax, bih::Trace &trace, void *parm = nullptr) override;
};

/// Geometry BIH tree
class GeometryBIHTree : public IGeometryTree {
public:
	~GeometryBIHTree() { Free(); }

/*!
    @name Interface core functions.
    @{
*/
	/// Raytrace the geometry tree.
	void RaytraceGeometry(GeometryTrace &trace, const Vector3 &s, const Vector3 &d, float l = -1.f) override { bih.RaytraceGeometry(trace, s, d, l); }
	/// Build tree from a geometry.
	bool BuildFromGeometry(Geometry *g) override { return bih.BuildFromGeometry(g); }
	/// Free all internal structures.
	void Free() override { bih.Free(); }
/// @}

private:
	GeometryBIH	bih;
};

} // core
} // gs
