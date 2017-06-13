// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/scene_system.h"
#include "foundation/frustum.h"
#include "foundation/vector3.h"
#include <memory>
#include <vector>

namespace gs {
namespace core {

class Node;

/// Light system
class LightSystem : public std::enable_shared_from_this<LightSystem>, public SceneSystem {
public:
	LightSystem();

	const std::string &GetAspect() const override;

	void AddComponent(sComponent c) override;
	void RemoveComponent(const sComponent &c) override;

	const std::vector<std::shared_ptr<Node>> &GetLights() const { return lights; }

	/// Get all lights in frustum.
	std::vector<std::shared_ptr<Node>> GetLightsInFrustum(const Vector3 &world_pos, const FrustumPlanes &frustum) const;
	/// Get closest lights.
	std::vector<std::shared_ptr<Node>> GetClosestLights(const Vector3 &world_pos) const;

	void DrawDebugPanel(render::RenderSystem &render_system) override;
	void DrawDebugVisuals(render::RenderSystem &render_system) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }

private:
	std::vector<std::shared_ptr<Node>> lights;

	bool draw_spot_frustum = true;
};

typedef std::shared_ptr<LightSystem> sLightSystem;

Frustum BuildSpotLightFrustum(const Node &node);

} // core
} // gs
