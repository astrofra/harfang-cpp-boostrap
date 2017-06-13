// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/light.h"
#include "foundation/reflection.h"
#include <memory>

namespace gs {
namespace core {

struct MouseEvent;

class Transform;
class Target;
class Environment;
class Collision;
class ConvexCollision;
class BoxCollision;
class SphereCollision;
class CapsuleCollision;
class MeshCollision;
class Metadata;

class Joint;
class SphericalJoint;
class D6Joint;
struct JointLimit;
class RigidBody;

class Camera;
class Object;
class Instance;
class Decorator;

struct NavigationLayer;
class NavigationGeometry;
class Navigation;
class NavigationSystem;

class Script;
struct LogicScript;
struct RenderScript;

class Skybox;
class Terrain;
class GrassField;
class SceneOverlay;
class SimpleGraphicSceneOverlay;

struct PostProcessComponent;
class SharpenPostProcess;
class RadialBlurPostProcess;
class ChromaticDispersionPostProcess;
class HSLPostProcess;

class SceneSystem;
class TransformSystem;
class CameraSystem;
class InstanceSystem;
class LightSystem;
class IPhysicSystem;
class RenderableSystem;

struct ScriptEngineEnv;
class ScriptSystem;
struct ScriptParamList;

} // core

void RegisterSceneReflection(TypeRegistry &registry);

DeclareTypeName(core::MouseEvent, "gs::core::MouseEvent")

DeclareTypeName(core::Scene, "gs::core::Scene")
DeclareTypeName(std::shared_ptr<core::Scene>, "gs::core::sScene")
DeclareTypeName(core::Node, "gs::core::Node")
DeclareTypeName(std::shared_ptr<core::Node>, "gs::core::sNode")

DeclareTypeName(core::Component, "gs::core::Component")
DeclareTypeName(std::shared_ptr<core::Component>, "gs::core::sComponent")
DeclareTypeName(core::Transform, "gs::core::Transform")
DeclareTypeName(core::Target, "gs::core::Target")
DeclareTypeName(core::Environment, "gs::core::Environment")
DeclareTypeName(core::Collision, "gs::core::Collision")
DeclareTypeName(core::ConvexCollision, "gs::core::ConvexCollision")
DeclareTypeName(core::BoxCollision, "gs::core::BoxCollision")
DeclareTypeName(core::SphereCollision, "gs::core::SphereCollision")
DeclareTypeName(core::CapsuleCollision, "gs::core::CapsuleCollision")
DeclareTypeName(core::MeshCollision, "gs::core::MeshCollision")
DeclareTypeName(core::Metadata, "gs::core::Metadata")

DeclareTypeName(core::Joint, "gs::core::Joint")
DeclareTypeName(core::SphericalJoint, "gs::core::SphericalJoint")
DeclareTypeName(core::D6Joint, "gs::core::D6Joint")
DeclareTypeName(core::JointLimit, "gs::core::JointLimit")
DeclareTypeName(core::RigidBody, "gs::core::RigidBody")

DeclareTypeName(core::Camera, "gs::core::Camera")
DeclareTypeName(core::Light, "gs::core::Light")
DeclareTypeName(core::Light::Model, "gs::core::Light::Model")
DeclareTypeName(core::Light::Shadow, "gs::core::Light::Shadow")
DeclareTypeName(core::Object, "gs::core::Object")
DeclareTypeName(core::Instance, "gs::core::Instance")
DeclareTypeName(core::Decorator, "gs::core::Decorator")

DeclareTypeName(std::vector<core::NavigationLayer>, "std::vector<gs::core::NavigationLayer>")
DeclareTypeName(core::NavigationLayer, "gs::core::NavigationLayer")
DeclareTypeName(core::NavigationGeometry, "gs::core::NavigationGeo")
DeclareTypeName(std::shared_ptr<core::NavigationGeometry>, "gs::core::sNavigationGeo")

DeclareTypeName(core::Navigation, "gs::core::Navigation")
DeclareTypeName(core::NavigationSystem, "gs::core::NavigationSystem")

DeclareTypeName(core::ScriptParamList, "gs::core::ScriptParamList")

DeclareTypeName(core::Script, "gs::core::Script")
DeclareTypeName(core::LogicScript, "gs::core::LogicScript")
DeclareTypeName(core::RenderScript, "gs::core::RenderScript")

DeclareTypeName(core::Skybox, "gs::core::Skybox")
DeclareTypeName(core::Terrain, "gs::core::Terrain")
DeclareTypeName(core::GrassField, "gs::core::GrassField")
DeclareTypeName(core::SceneOverlay, "gs::core::SceneOverlay")
DeclareTypeName(core::SimpleGraphicSceneOverlay, "gs::core::SimpleGraphicSceneOverlay")

DeclareTypeName(core::PostProcessComponent, "gs::core::PostProcessComponent")
DeclareTypeName(core::SharpenPostProcess, "gs::core::SharpenPostProcess")
DeclareTypeName(core::RadialBlurPostProcess, "gs::core::RadialBlurPostProcess")
DeclareTypeName(core::ChromaticDispersionPostProcess, "gs::core::ChromaticDispersionPostProcess")
DeclareTypeName(core::HSLPostProcess, "gs::core::HSLPostProcess")

DeclareTypeName(core::SceneSystem, "gs::core::SceneSystem")
DeclareTypeName(core::TransformSystem, "gs::core::TransformSystem")
DeclareTypeName(core::CameraSystem, "gs::core::CameraSystem")
DeclareTypeName(core::InstanceSystem, "gs::core::InstanceSystem")
DeclareTypeName(core::LightSystem, "gs::core::LightSystem")
DeclareTypeName(core::IPhysicSystem, "gs::core::IPhysicSystem")
DeclareTypeName(core::RenderableSystem, "gs::core::RenderableSystem")

DeclareTypeName(core::ScriptEngineEnv, "gs::core::ScriptEngineEnv")
DeclareTypeName(std::shared_ptr<core::ScriptEngineEnv>, "gs::core::sScriptEngineEnv")
DeclareTypeName(core::ScriptSystem, "gs::core::ScriptSystem")

} // gs
