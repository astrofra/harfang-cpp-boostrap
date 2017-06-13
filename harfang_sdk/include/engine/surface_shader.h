// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/material.h"
#include "engine/render_pass.h"
#include "engine/renderable.h"
#include "engine/gpu_shader.h"

namespace gs {
namespace render {

class RenderSystem;

// Variants of a shader used by the rendering pipeline to draw primitives.
class SurfaceShader : public gpu::Resource {
public:
	explicit SurfaceShader(const char *name = "") : gpu::Resource(name), shaders_to_create(0), surface_draw_state(0) {}

	uint GetSurfaceDrawState() const { return surface_draw_state; }

	bool SetUserUniformValue(const char *name, Vector4 value);
	bool SetUserUniformValue(const char *name, gpu::sTexture value);

	bool Create(RenderSystem &render_system, core::sShader shader);
	void Free();

	gpu::sShader pass_shaders[2][RenderPass::ShaderCount]; // non-instantiated/instantiated

	/*!
		@short Return the list of variables in the shader
		@note Some variables may be absent from a particular shader variant.
	*/
	const std::shared_ptr<core::ShaderVariableTable> &GetVariables() const { return variables; }

private:
	std::shared_ptr<core::ShaderVariableTable> variables;

	friend void OnSurfaceShaderPassReady(SurfaceShader &surface_shader, RenderPass::Shader shader);

	uint8_t shaders_to_create;
	uint8_t surface_draw_state;
};

typedef std::shared_ptr<SurfaceShader> sSurfaceShader;

/// Get the renderable context target render pass for a surface shader .
RenderPass::Pass GetSurfaceShaderTargetPassForRenderableContext(SurfaceShader &surface_shader, IRenderable::Context ctx);

} // render
} // gs
