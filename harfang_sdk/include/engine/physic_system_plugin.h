// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/physic_system.h"

namespace gs {
namespace core {

class ComponentFactory;

/// Register physic system components into the engine factory.
void RegisterPhysicSystemComponents(ComponentFactory &factory);

/// Physic system plugin interface.
struct IPhysicSystemPlugin {
	virtual sIPhysicSystem MakePhysicSystem() = 0;

	virtual sComponent MakeRigidBody() = 0;
	virtual sComponent MakeBoxCollision() = 0;
	virtual sComponent MakeCapsuleCollision() = 0;
	virtual sComponent MakeSphereCollision() = 0;
	virtual sComponent MakeConvexCollision() = 0;
	virtual sComponent MakeMeshCollision() = 0;
	virtual sComponent MakeSphericalJoint() = 0;
	virtual sComponent MakeD6Joint() = 0;
};

/// Global physic engine plugin instance.
extern IPhysicSystemPlugin *g_physic_system_plugin;

/// Create a physic system.
sIPhysicSystem MakePhysicSystem();

/// Create a rigid body component.
sComponent MakeRigidBody();
/// Create a box collision component.
sComponent MakeBoxCollision();
/// Create a capsule collision component.
sComponent MakeCapsuleCollision();
/// Create a sphere collision component.
sComponent MakeSphereCollision();
/// Create a convex collision component.
sComponent MakeConvexCollision();
/// Create a mesh collision component.
sComponent MakeMeshCollision();
/// Create a spherical joint component.
sComponent MakeSphericalJoint();
/// Create a 6-DOF joint component.
sComponent MakeD6Joint();

} // core
} // gs
