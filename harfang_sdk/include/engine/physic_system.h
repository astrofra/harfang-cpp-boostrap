// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/collision.h"
#include "engine/collision_pair.h"
#include "engine/joint.h"
#include "engine/node.h"
#include "engine/rigid_body.h"
#include "engine/scene_system.h"
#include "foundation/signal.h"
#include "foundation/vector.h"

namespace gs {
namespace core {

struct PhysicTrace {
	Vector3 p, n;
	Node *i = nullptr;
};

/// Physic system interface.
class IPhysicSystem : public SceneSystem {
public:
	IPhysicSystem();

	const std::string &GetAspect() const override;

	/// Add a component to the system.
	void AddComponent(sComponent component) override;
	/// Remove a component from the system.
	void RemoveComponent(const sComponent &component) override;

	/// Return the implementation name.
	virtual const std::string &GetImplementationName() const = 0;

	DeclSystemBaseGetSetAsync(IPhysicSystem, float, Timestep, timestep);
	DeclSystemBaseGetSetAsync(IPhysicSystem, bool, ForceRigidBodyToSleepOnCreation, force_sleep_body);
	DeclSystemBaseGetSetAsync(IPhysicSystem, uint, ForceRigidBodyAxisLockOnCreation, force_axis_lock);

	DeclSystemBaseGetSetAsyncNoImpl(IPhysicSystem, Vector3, Gravity);

	/// Raycast world.
public:
	virtual bool Raycast(const Vector3 &start, const Vector3 &direction, PhysicTrace &hit, uint8_t collision_layer_mask = 0xff, float max_distance = -1) = 0;

	///
	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, bool, RigidBodyIsSleeping);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, Vector3, RigidBodyAngularVelocity);
	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, Vector3, RigidBodyLinearVelocity);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, float, RigidBodyLinearDamping);
	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, float, RigidBodyAngularDamping);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, float, RigidBodyStaticFriction);
	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, float, RigidBodyDynamicFriction);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, float, RigidBodyRestitution);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, RigidBodyType, RigidBodyType);

	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, uint8_t, RigidBodyAxisLock);
	DeclSystemBaseComponentGetSetAsync(IPhysicSystem, RigidBody, uint8_t, RigidBodyCollisionLayer);

public:
	virtual Vector3 GetRigidBodyVelocity(const RigidBody *body, const Vector3 &p) const = 0;
	void SetRigidBodyVelocity(RigidBody *body, const Vector3 &V, const Vector3 &p) { commit_queue.queue<void>(std::bind(&IPhysicSystem::commit_SetRigidBodyVelocity, this, body, V, p)); }

protected:
	virtual void commit_SetRigidBodyVelocity(RigidBody *body, const Vector3 &V, const Vector3 &p) = 0;

public:
	void RigidBodyApplyLinearImpulse(RigidBody *body, const Vector3 &I);
	void RigidBodyApplyLinearForce(RigidBody *body, const Vector3 &F);
	void RigidBodyApplyTorque(RigidBody *body, const Vector3 &T);

	void RigidBodyApplyImpulse(RigidBody *body, const Vector3 &I, const Vector3 &p);
	void RigidBodyApplyForce(RigidBody *body, const Vector3 &F, const Vector3 &p);

	void RigidBodyResetWorld(RigidBody *body, const Matrix4 &M);

protected:
	virtual void commit_RigidBodyApplyLinearImpulse(RigidBody *body, const Vector3 &I) = 0;
	virtual void commit_RigidBodyApplyLinearForce(RigidBody *body, const Vector3 &F) = 0;
	virtual void commit_RigidBodyApplyTorque(RigidBody *body, const Vector3 &T) = 0;

	virtual void commit_RigidBodyApplyImpulse(RigidBody *body, const Vector3 &I, const Vector3 &p) = 0;
	virtual void commit_RigidBodyApplyForce(RigidBody *body, const Vector3 &F, const Vector3 &p) = 0;

	virtual void commit_RigidBodyResetWorld(RigidBody *body, const Matrix4 &M) = 0;

public:
	void OnCollisionModified(const sCollision &collision);
	void OnJointModified(const sJoint &joint);

	/// Return collision pairs for the last update.
	const std::vector<CollisionPair> &GetCollisionPairs() const { return collision_pairs[current_collision_pair_array_index]; }
	/// Return collision pairs involving a specific node for the last update.
	std::vector<CollisionPair> GetCollisionPairs(const sNode &node) const;

	/// Return true if the system has at least one collision pair involving a specified node.
	bool HasCollided(const sNode &node) const;
	bool HasCollided(const sNode &node_a, const sNode &node_b) const;

	void SetCollisionLayerPairState(uint16_t layer_a, uint16_t layer_b, bool enable_collision);
	bool GetCollisionLayerPairState(uint16_t layer_a, uint16_t layer_b) const;

protected:
	std::vector<sRigidBody> bodies_to_create, bodies_to_delete; // shared is required to account for the one frame lag until the list is processed
	std::vector<sRigidBody> bodies_requiring_collision_update;

	std::vector<sCollision> collision_to_create, collision_to_delete;

	std::vector<sJoint> joints_to_create, joint_to_delete, joints_requiring_update;

	std::vector<CollisionPair> collision_pairs[2];
	uint8_t current_collision_pair_array_index;

	uint8_t layer_to_layer_collision_bitmask[8]; // with which other layer will each layer collide

	virtual void OnCollisionLayerMaskModified() {}
};

typedef std::shared_ptr<IPhysicSystem> sIPhysicSystem;

} // core
} // gs
