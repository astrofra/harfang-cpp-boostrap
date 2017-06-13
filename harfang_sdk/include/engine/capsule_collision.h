// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/collision.h"

namespace gs {
namespace core {

/// Capsule collision component
class CapsuleCollision : public std::enable_shared_from_this<CapsuleCollision>, public Collision {
public:
	CapsuleCollision();

	decl_component_defaults(CapsuleCollision, "CapsuleCollision");

	comp_decl_member_get_sync_set_async_noimpl(CapsuleCollision, float, Length, length);
	comp_decl_member_get_sync_set_async_noimpl(CapsuleCollision, float, Radius, radius);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
