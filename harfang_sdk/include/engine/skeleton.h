// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/node.h"
#include "foundation/matrix4.h"

namespace gs {
namespace core {

struct Skeleton {
	std::vector<sNode> bones;
	std::vector<Matrix4> bones_mtx, previous_bones_mtx;
};

typedef std::shared_ptr<Skeleton> sSkeleton;

} // core
} // gs
