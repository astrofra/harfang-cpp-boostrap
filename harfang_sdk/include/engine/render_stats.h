// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/time.h"
#include <cstdint>

namespace gs {
namespace render {

struct Statistics {
	Statistics();

	void Reset();

	time_t frame_start;
	uint32_t render_primitive_drawn, line_drawn, triangle_drawn, instanced_batch_count, instanced_batch_size;
};

} // render
} // gs
