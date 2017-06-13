// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <cstddef>

namespace gs {

// Decorator class to track an allocator key metrics.
template <class Allocator> struct AllocatorProfiler {
	struct Header {
		size_t size;
	};

	struct Profile {
		uint alloc_count = 0;
		uint alive_count = 0, alive_count_peak = 0;
		size_t size = 0, size_peak = 0;
	};

	Profile profile;

	void *malloc(size_t size) {
		auto h = reinterpret_cast<Header *>(Allocator::malloc(sizeof(Header) + size));
		h->size = size;

		++profile.alloc_count;
		++profile.alive_count;
		if (profile.alive_count > profile.alive_count_peak)
			profile.alive_count_peak = profile.alive_count;

		profile.size += size;
		if (profile.size > profile.size_peak)
			profile.size_peak = profile.size;

		return h + 1;
	}

	void free(void *p) {
		if (p) {
			auto h = reinterpret_cast<Header *>(p) - 1;
			profile.size -= h->size;

			Allocator::free(h);
			--profile.alive_count;
		}
	}
};

} // gs
