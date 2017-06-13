// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/shader.h"

namespace gs {
namespace core {

enum ShaderType : uint8_t;
struct ShaderValue;

bool ParseShaderValue(const std::string &v, ShaderValue &out, ShaderType, bool use_naked_path = false);
std::string ShaderValueToString(const ShaderValue &in, ShaderType, bool use_naked_path = false);

/// Load a shader input variables declaration.
bool LoadShaderVariables(const char *name, std::vector<std::unique_ptr<ShaderVariable>> &out);

/// Load a shader from source.
bool LoadShader(Shader &shader, const char *source);

/// Transfer varyings from a shader variant to another variant. The variant previous content is not lost.
void TransferShaderVariantVaryings(ShaderVariant &out, const ShaderVariant &in);

} // core
} // gs
