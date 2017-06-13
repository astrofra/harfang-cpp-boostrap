// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/get_type_name.h"
#include "engine/node.h"
#include <string>

namespace gs {
namespace render {

/// Render pass
struct RenderPass {
	enum Pass : uint8_t { Opaque = 0, Transparent, FramebufferDependent, Shadow, PassCount };

	enum Shader : uint8_t {
		Depth = 0,

		DS_GBufferMRT4, ///< deferred MRT 4 buffers

		FS_Constant,
		FS_PointLight,
		FS_PointLightShadowMapping,
		FS_LinearLight,
		FS_LinearLightShadowMapping,
		FS_SpotLight,
		FS_SpotLightShadowMapping,
		FS_SpotLightProjection,
		FS_SpotLightProjectionShadowMapping,

		PP_NormalDepth,
		PP_Velocity,

		Picking, ///< node id rendering

		ShaderCount
	};

	RenderPass(Pass g, Shader p) : pass(g), shader(p), light(nullptr) {}
	RenderPass() : pass(PassCount), shader(ShaderCount), light(nullptr) {}

	inline bool operator==(const RenderPass &p) const { return pass == p.pass && shader == p.shader && light == p.light; }
	inline bool operator!=(const RenderPass &p) const { return !(*this == p); }

	Pass pass;
	Shader shader;

	core::sNode light;
};

} // render

DeclareTypeName(render::RenderPass, "gs::render::RenderPass")

} // gs

namespace std {

string to_string(const gs::render::RenderPass &pass);
string to_string(gs::render::RenderPass::Pass pass_pass);
string to_string(gs::render::RenderPass::Shader pass_shader);

} // std
