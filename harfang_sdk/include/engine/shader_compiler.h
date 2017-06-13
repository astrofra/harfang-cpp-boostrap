// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/gpu_shader.h"
#include "engine/shader.h"
#include <string>

namespace gs {
namespace gpu {

class Renderer;

/// GPU shader compiler interface
struct IShaderCompiler {
	virtual ~IShaderCompiler() {}
	virtual bool Compile(gpu::Renderer &renderer, std::shared_ptr<gpu::Shader> shader, std::shared_ptr<core::ShaderVariableTable> var_table, const std::string &vertex_source, const std::string &pixel_source) = 0;
};

} // gpu
} // gs
