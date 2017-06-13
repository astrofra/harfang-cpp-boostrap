// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <limits>

#include "foundation/types.h"

namespace gs {

template <typename T> inline T pack_float(float v) {
	if (std::is_signed<T>::value)
		return T(types::Clamp(v, -1.f, 1.f) * std::numeric_limits<T>::max());
	return T(types::Clamp(v, 0.f, 1.f) * std::numeric_limits<T>::max());
}

template <typename T> inline float unpack_float(T v) { return float(v) / std::numeric_limits<T>::max(); }

} // gs
