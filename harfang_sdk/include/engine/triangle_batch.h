// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/material.h"
#include "engine/resource.h"
#include "foundation/color.h"
#include "foundation/types.h"
#include "foundation/vector2.h"
#include "foundation/vector3.h"
#include <vector>

namespace gs {
namespace gpu { struct Texture; }
namespace render {

class TriangleBatch {
public:
	explicit TriangleBatch(uint batch_max_tri = 128);

	void DrawTriangle(uint triangle_count, uint attrib_count, const Vector3 *, const uint16_t *, const Color *, const Vector2 *uv, const std::shared_ptr<gpu::Texture> &tex);
	void Flush();

private:
	uint batch_max_triangle_count;
	uint batch_triangle_count, batch_attrib_offset;

	std::vector<uint16_t> batch_idx;
	std::vector<Vector3> batch_vtx;
	std::vector<Color> batch_col;
	std::vector<Vector2> batch_uv;

	std::shared_ptr<gpu::Texture> batch_t;
};

} // render
} // gs
