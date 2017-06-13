// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include "engine/texture.h"
#include "engine/shader.h"
#include "foundation/get_type_name.h"

namespace gs {
namespace gpu {

struct ShaderValue;

typedef std::vector<ShaderValue> ShaderValues;

/// GPU shader.
struct Shader : public Resource {
	explicit Shader(const char *name) : Resource(name) {}
	Shader(const Shader &shader) = delete;

	virtual bool UsesBuiltin(core::ShaderVariable::Semantic semantic) const = 0;

	core::sShaderVariableTable variable_table;
	ShaderValues values;
};

typedef std::shared_ptr<Shader> sShader;

sShader MakeShader();

struct ShaderValue {
	ShaderValue() { iv[0] = iv[1] = iv[2] = iv[3] = 0; }

	union {
		int iv[4];
		uint uv[4];
		float fv[4];
	};

	sTexture texture;
	core::TextureUnitConfig tex_unit_cfg;
};

gpu::ShaderValue CoreShaderValueToGpuShaderValue(Renderer &renderer, core::ShaderType type, const core::ShaderValue &in);

void ShaderDeleter(gpu::Shader *shader, std::weak_ptr<gpu::Renderer> renderer_weak, task_affinity worker);

} // gpu

DeclareTypeName(gpu::Shader, "gs::gpu::Shader")
DeclareTypeName(gpu::sShader, "gs::gpu::sShader")

} // gs
