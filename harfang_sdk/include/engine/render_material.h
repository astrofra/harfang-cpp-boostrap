// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/surface_shader.h"

namespace gs {
namespace render {

/// Render material
class Material : public gpu::Resource {
public:
	explicit Material(const char *name = "") : Resource(name) {}

	/// Re-create from core material.
	bool Create(RenderSystem &render_system, core::sMaterial mat);
	/// Free material.
	void Free();

	/// Clone material.
	std::shared_ptr<Material> Clone() const;

	bool IsReadyOrFailed() const override;

	inline const sSurfaceShader &GetSurfaceShader() const { return surface_shader; }
	void SetSurfaceShader(sSurfaceShader surface_shader);

	gpu::ShaderValues values;

	/// Return a material value slot.
	gpu::ShaderValue *GetValue(const char *name);

private:
	sSurfaceShader surface_shader;
};

bool SaveRenderMaterial(const Material &mat, const char *path = nullptr);

/// Clone a render material.
std::shared_ptr<Material> Clone(const Material &mat);

typedef std::shared_ptr<Material> sMaterial;

} // render
} // gs
