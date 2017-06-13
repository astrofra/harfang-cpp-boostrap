// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/scene_system.h"

namespace gs {
namespace core {

class CameraSystem : public std::enable_shared_from_this<CameraSystem>, public SceneSystem {
public:
	CameraSystem();

	const std::string &GetAspect() const override;

	void AddComponent(sComponent c) override;
	void RemoveComponent(const sComponent &c) override;

	std::shared_ptr<SceneSystem> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
