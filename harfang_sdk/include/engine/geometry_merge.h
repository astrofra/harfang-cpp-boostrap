// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <memory>

namespace gs { class Matrix4;
namespace core {

class Geometry;

std::shared_ptr<Geometry> GeometryMerge(const char *name, uint count, const std::shared_ptr<Geometry> *geo, const Matrix4 *mtx);

} // core
} // gs
