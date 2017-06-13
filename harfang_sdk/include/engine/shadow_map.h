// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderable.h"
#include "foundation/task_set.h"

namespace gs { class task_set;
namespace render { class RenderSystem;

void PrepareShadowMap(const RenderSystem &render_system, const IRenderableList &renderables, const core::Node &light, bool rebuild_frustum_primitive_lists, const stask_set &set);
void DrawShadowMap(RenderSystem &render_system, const core::Node &light, gpu::sRenderTarget shadow_map_fbo);

} // render
} // gs
