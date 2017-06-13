// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry.h"
#include "engine/collision.h"

namespace gs {
namespace core {

/// Mesh collision component
class MeshCollision : public std::enable_shared_from_this<MeshCollision>, public Collision {
public:
	MeshCollision();

	decl_component_defaults(MeshCollision, "MeshCollision");

	comp_decl_member_get_sync_set_async_noimpl(MeshCollision, sGeometry, Geometry, geometry);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
