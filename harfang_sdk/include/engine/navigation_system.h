// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/recast_wrapper.h"
#include "engine/scene_system.h"
#include <mutex>

namespace gs {
namespace core {

class Node;

class NavigationSystem : public std::enable_shared_from_this<NavigationSystem>, public SceneSystem {
public:
	NavigationSystem();

	const std::string &GetAspect() const override;

	void Update(time_t dt = 0) override;

	void AddComponent(sComponent component) override;
	void RemoveComponent(const sComponent &component) override;

	/// Find a path between two world positions in the system navigation database.
	bool FindPathTo(const Vector3 &from, const Vector3 &to, NavigationPath &path, uint layer_index = 0);

	const NavigationConfig &GetConfig() const { return config; }

	void DrawDebugVisuals(render::RenderSystem &render_system) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

private:
	NavigationConfig config;

	std::vector<std::shared_ptr<Node>> navigation_nodes;
	std::vector<std::shared_ptr<Component>> navigation_components;

	std::mutex recast_mutex;
};

} // core
} // gs
