// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cfloat>
#include "foundation/vector3.h"

namespace gs {
namespace sat {

/// SAT overlap test results
enum Overlap { Outside, Inside, Clipped };

/// Helper function to test overlap on a given axis.
Overlap TestOverlap(const Vector3 &axis, int ca, const Vector3 *a, int cb, const Vector3 *b);

} // sat
} // gs
