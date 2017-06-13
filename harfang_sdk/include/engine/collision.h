// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/matrix4.h"
#include "engine/component.h"
#include "engine/node.h"

namespace gs {
namespace core {

/// Collision component
class Collision : public Component {
public:
	Collision();

	comp_decl_member_get_sync_set_async_noimpl(Collision, float, Mass, mass);
	comp_decl_member_get_sync_set_async_noimpl(Collision, Matrix4, Matrix, matrix);

	void *impl;

protected:
	void OnModified();
};

typedef std::shared_ptr<Collision> sCollision;

/// Return true if the passed node has at least one collision component.
bool NodeHasCollisionAspect(const Node &node);
/// Return true if the component implements a collision aspect.
bool IsCollisionComponent(const Component &component);

} // core
} // gs
