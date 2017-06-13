// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/gpu_shader.h"
#include "engine/component.h"

namespace gs {
namespace core {

/// Skybox component
class Skybox : public std::enable_shared_from_this<Skybox>, public Component {
	decl_component_defaults(Skybox, "Skybox");

	Skybox();

	comp_decl_member_get_sync_set_async(Skybox, gpu::sShader, Shader, shader);
	comp_decl_member_get_sync_set_async(Skybox, gpu::sTexture, LayerA, layer_a);
	comp_decl_member_get_sync_set_async(Skybox, gpu::sTexture, LayerB, layer_b);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

} // core
} // gs
