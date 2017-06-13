// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include "engine/joint.h"

namespace gs {
namespace core {

/// Spherical joint component
class SphericalJoint : public std::enable_shared_from_this<SphericalJoint>, public Joint {
public:
	SphericalJoint();

	decl_component_defaults(SphericalJoint, "SphericalJoint");

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
