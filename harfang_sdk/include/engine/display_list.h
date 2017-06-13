// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/vertex_layout.h"
#include "engine/render_material.h"
#include "engine/gpu_buffer.h"

namespace gs {
namespace render {

struct DisplayList {
	DisplayList() : idx_count(0), idx_type(core::IndexUShort) {}
	DisplayList(uint idx_count_, gpu::Buffer *idx_, gpu::Buffer *vtx_, const core::VertexLayout &vtx_layout_, const MinMax &minmax_, Material *material_,
		core::IndexType idx_type_ = core::IndexUShort)
		: idx_count(idx_count_), idx_type(idx_type_), idx(idx_), vtx(vtx_), vtx_layout(vtx_layout_), minmax(minmax_), material(material_) {}

	uint idx_count;
	core::IndexType idx_type;

	gpu::sBuffer idx;
	gpu::sBuffer vtx;
	core::VertexLayout vtx_layout;

	MinMax minmax;
	sMaterial material;
};

} // render
} // gs
