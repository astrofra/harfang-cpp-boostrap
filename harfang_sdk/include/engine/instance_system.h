// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "engine/group.h"
#include "engine/scene_system.h"
#include <string>

namespace gs {
namespace render { class RenderSystem; }
namespace core {

class Scene;

/// Instance system
class InstanceSystem : public std::enable_shared_from_this<InstanceSystem>, public SceneSystem {
public:
	InstanceSystem(std::shared_ptr<Scene> scene, std::shared_ptr<render::RenderSystem> render_system);

	const std::string &GetAspect() const override;

	void AddComponent(sComponent c) override;
	void RemoveComponent(const sComponent &c) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

private:
	std::weak_ptr<Scene> scene;
	std::shared_ptr<render::RenderSystem> render_system;

	bool Instantiate(Component &c);
	void Deinstantiate(Component &c);
};

} // core
} // gs
