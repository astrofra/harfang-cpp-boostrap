// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include "foundation/document.h"
#include <memory>

namespace gs {
namespace render { class RenderSystem; }
namespace core {

class Node;

/// Scene serialization context
struct SceneSerializationContext : SerializationContext {
	explicit SceneSerializationContext(std::shared_ptr<render::RenderSystem> render_system);

	const std::string &GetType() const override {
		static std::string type = "SceneSerializationContext";
		return type;
	}

	std::shared_ptr<render::RenderSystem> render_system;
};

/// Scene deserialization context
struct SceneDeserializationContext : DeserializationContext {
	explicit SceneDeserializationContext(std::shared_ptr<render::RenderSystem> render_system, bool instance = false);

	const std::string &GetType() const override {
		static std::string type = "SceneDeserializationContext";
		return type;
	}

	std::shared_ptr<render::RenderSystem> render_system;
	bool is_deserializing_instance;

	std::map<uint, std::shared_ptr<Node>> node_uid_map;
	std::vector<std::shared_ptr<Node>> GetNodes() const;
};

} // core
} // gs
