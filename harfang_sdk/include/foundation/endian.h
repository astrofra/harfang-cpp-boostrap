// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"

namespace gs {
namespace endian {

enum Config { Undefined = 0, Big, Little, Motorola = Big, Intel = Little };

/// Swap bytes of memory.
void SwapBytes(void *, size_t);

/// Return the current host memory configuration.
Config GetHostConfiguration();

/// Convert a memory block in place to the host configuration.
void *ToHostMem(void *, size_t, Config = Big);

/// Convert a value to the host configuration.
template <class T> T ToHost(const T &v, Config cfg = Big) {
	if (GetHostConfiguration() == cfg)
		return v;

	T host_value = v;
	SwapBytes(&host_value, sizeof(T));
	return host_value;
}

} // endian
} // gs
