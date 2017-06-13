// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3_api.h"

namespace gs {
namespace core {

struct TangentFrame {
	Vector3 T, B;
};

inline bool operator==(const TangentFrame &a, const TangentFrame &b) { return a.T == b.T && a.B == b.B; }
inline bool operator!=(const TangentFrame &a, const TangentFrame &b) { return a.T != b.T || a.B != b.B; }

} // core
} // gs
