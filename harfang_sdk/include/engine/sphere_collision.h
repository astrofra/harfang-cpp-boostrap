// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/collision.h"

namespace gs {
namespace core {

/// Sphere collision component
class SphereCollision : public std::enable_shared_from_this<SphereCollision>, public Collision {
public:
	SphereCollision();

	decl_component_defaults(SphereCollision, "SphereCollision");

	comp_decl_member_get_sync_set_async_noimpl(SphereCollision, float, Radius, radius);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
