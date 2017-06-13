// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <memory>

#include "engine/texture.h"
#include "foundation/get_type_name.h"

namespace gs {
namespace gpu {

/// GPU render target
struct RenderTarget {
	static const int MaxColorTextureCount = 8;

	uint color_texture_count = 0;
	sTexture color_texture[MaxColorTextureCount], depth_texture;
};

typedef std::shared_ptr<RenderTarget> sRenderTarget;

void RenderTargetDeleter(gpu::RenderTarget *rt, std::weak_ptr<gpu::Renderer> renderer_weak, task_affinity worker);

} // gpu
} // gs
