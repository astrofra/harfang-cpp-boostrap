// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry.h"
#include "engine/collision.h"

namespace gs {
namespace core {

/// Convex collision component
class ConvexCollision : public std::enable_shared_from_this<ConvexCollision>, public Collision {
public:
	ConvexCollision();

	decl_component_defaults(ConvexCollision, "ConvexCollision");

	comp_decl_member_get_sync_set_async_noimpl(ConvexCollision, sGeometry, Geometry, geometry);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
