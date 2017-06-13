// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"

namespace gs {
namespace core {

/*!
	@short Optimize a list of triangle indices.

	The optimizer reorder the indices in order to maximize cache hits.
	You can specify the target architecture vertex cache size.

	@note This function can be called multiple times if needed.
*/
void OptimizeIndices(uint idx_count, uint vtx_count, const uint *in_idx, uint *out_idx, uint cache_size = 32);

} // core
} // gs
