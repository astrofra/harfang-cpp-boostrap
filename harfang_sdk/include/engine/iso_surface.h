// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include <future>
#include <memory>
#include <vector>

namespace gs {
namespace render {
class RenderSystem;
class Material;
class Geometry;
} // render

namespace core {

class Geometry;

struct IsoSurface {
	static const int vertex_map_count = 256;

	IsoSurface();

	std::vector<uint> indices;
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;

	void Clear();
	void AddTriangle(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);

	inline uint GetTriangleCount() const { return indices.size() / 3; }

private:
	uint AddVertex(const Vector3 &v);

	std::vector<uint> vertex_map[vertex_map_count];
};

typedef std::shared_ptr<IsoSurface> sIsoSurface;

void PolygoniseIsoSurface(uint width, uint height, uint depth, const float *val, float isolevel, IsoSurface &out, const Vector3 &unit = Vector3::One);
void IsoSurfaceToCoreGeometry(const IsoSurface &iso, Geometry &out);

std::future<void> IsoSurfaceToRenderGeometry(std::shared_ptr<render::RenderSystem> render_system, sIsoSurface iso, std::shared_ptr<render::Geometry> geo, std::shared_ptr<render::Material> mat);
std::future<void> PolygoniseIsoSurfaceToRenderGeometry(std::shared_ptr<render::RenderSystem> render_system, std::shared_ptr<render::Geometry> geo, std::shared_ptr<render::Material> mat, uint width, uint height, uint depth, const float *val, float isolevel, sIsoSurface iso, const Vector3 &unit = Vector3::One);

} // core
} // gs
