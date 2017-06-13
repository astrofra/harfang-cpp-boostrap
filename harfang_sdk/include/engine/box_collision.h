// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include "engine/collision.h"

namespace gs {
namespace core {

/// Box collision component
class BoxCollision : public std::enable_shared_from_this<BoxCollision>, public Collision {
public:
	BoxCollision();

	decl_component_defaults(BoxCollision, "BoxCollision");

	comp_decl_member_get_sync_set_async_noimpl(BoxCollision, Vector3, Dimensions, dimensions);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
