// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"

namespace gs {
namespace core {

struct TransformModifier : Component {
	virtual void ModifyTransform(Matrix4 &world) = 0;
};

} // core
} // gs
