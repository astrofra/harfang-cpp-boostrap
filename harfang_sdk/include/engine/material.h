// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <memory>

#include "engine/shader.h"

namespace gs {
namespace core {

struct MaterialValue : ShaderValue {
	MaterialValue() : type(ShaderNoType) {}

	std::string name;
	ShaderType type;
};

bool operator==(const MaterialValue &a, const MaterialValue &b);

/*!
	@short Material.
	A material associates a shader and a set of values for the shader inputs.
*/
struct Material {
	Material() { values.reserve(8); }

	std::string name, shader;
	std::vector<MaterialValue> values;

	MaterialValue *GetValue(const char *name);
};

typedef std::shared_ptr<Material> sMaterial;

} // core
} // gs
