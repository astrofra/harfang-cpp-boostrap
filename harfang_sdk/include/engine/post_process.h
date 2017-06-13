// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "foundation/reflection.h"
#include "foundation/vector2.h"

namespace gs {

namespace render { class RenderSystem; }

namespace gpu {
struct RenderTarget;
struct Shader;
struct Texture;
} // gpu

namespace core {

/// Post-process interface
struct PostProcessComponent : Component {
	/*!
		@short Apply post-process to the input textures.
		@return True to swap the frame ping-pong texture set, false if the
		post-process is done directly over the input.
	*/
	virtual bool Apply(render::RenderSystem &rs, const std::shared_ptr<gpu::RenderTarget> &rt, const std::shared_ptr<gpu::Texture> &t_in, const std::shared_ptr<gpu::Texture> &t_out) = 0;
};

// Sharpen post-process
class SharpenPostProcess : public std::enable_shared_from_this<SharpenPostProcess>, public PostProcessComponent {
public:
	SharpenPostProcess();

	decl_component_defaults(SharpenPostProcess, "PostProcess");
	comp_decl_member_get_sync_set_async(SharpenPostProcess, float, Strength, strength);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	bool Apply(render::RenderSystem &rs, const std::shared_ptr<gpu::RenderTarget> &rt, const std::shared_ptr<gpu::Texture> &t_in, const std::shared_ptr<gpu::Texture> &t_out) override;

private:
	std::shared_ptr<gpu::Shader> shader;
};

// Radial blur post-process
class RadialBlurPostProcess : public std::enable_shared_from_this<RadialBlurPostProcess>, public PostProcessComponent {
public:
	RadialBlurPostProcess();

	decl_component_defaults(RadialBlurPostProcess, "PostProcess");

	comp_decl_member_get_sync_set_async_validated(RadialBlurPostProcess, float, Strength, strength, ClampToZero);
	comp_decl_member_get_sync_set_async(RadialBlurPostProcess, Vector2, Center, center);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	bool Apply(render::RenderSystem &rs, const std::shared_ptr<gpu::RenderTarget> &rt, const std::shared_ptr<gpu::Texture> &t_in, const std::shared_ptr<gpu::Texture> &t_out) override;

private:
	std::shared_ptr<gpu::Shader> shader;
};

// Chromatic dispersion post-process
class ChromaticDispersionPostProcess : public std::enable_shared_from_this<ChromaticDispersionPostProcess>, public PostProcessComponent {
public:
	ChromaticDispersionPostProcess();

	decl_component_defaults(ChromaticDispersionPostProcess, "PostProcess");
	comp_decl_member_get_sync_set_async(ChromaticDispersionPostProcess, float, Width, width);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	bool Apply(render::RenderSystem &rs, const std::shared_ptr<gpu::RenderTarget> &rt, const std::shared_ptr<gpu::Texture> &t_in, const std::shared_ptr<gpu::Texture> &t_out) override;

private:
	std::shared_ptr<gpu::Shader> shader;
};

// Hue/Saturation/Luminance post-process
class HSLPostProcess : public std::enable_shared_from_this<HSLPostProcess>, public PostProcessComponent {
public:
	HSLPostProcess();

	decl_component_defaults(HSLPostProcess, "PostProcess");
	comp_decl_member_get_sync_set_async(HSLPostProcess, float, H, H);
	comp_decl_member_get_sync_set_async(HSLPostProcess, float, S, S);
	comp_decl_member_get_sync_set_async(HSLPostProcess, float, L, L);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	bool Apply(render::RenderSystem &rs, const std::shared_ptr<gpu::RenderTarget> &rt, const std::shared_ptr<gpu::Texture> &t_in, const std::shared_ptr<gpu::Texture> &t_out) override;

private:
	std::shared_ptr<gpu::Shader> shader;
};

class ComponentFactory;

void RegisterCorePostProcessComponents(ComponentFactory &factory);

void ApplyPostProcesses(render::RenderSystem &render_system, const std::vector<sComponent> &post_process_components);

} // core
} // gs
