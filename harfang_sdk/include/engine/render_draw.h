// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/render_primitive.h"
#include "engine/render_pass.h"
#include "engine/renderable.h"

namespace gs {
namespace core { class LightSystem; }
namespace gpu { struct RenderTarget; }
namespace render {

void SetSurfaceDrawState(gpu::Renderer &renderer, uint surface_draw_state, RenderPass::Pass pass, bool is_light_pass);

void DrawPrimitivesForward(RenderSystem &render_system, const IRenderableList &renderables, core::LightSystem &light_system, const PrimitiveLists &prim_lists, RenderPass::Pass pass);
void DrawFramebufferDependentPrimitivesForward(RenderSystem &render_system, const IRenderableList &renderables, core::LightSystem &light_system, const PrimitiveLists &prim_lists);

void DrawPrimitiveListsDeferred(RenderSystem &render_system, const IRenderableList &renderables, core::LightSystem &light_system, const PrimitiveLists &prims);
void DrawPrimitiveListsForward(RenderSystem &render_system, const IRenderableList &renderables, core::LightSystem &light_system, const PrimitiveLists &prims);

bool DrawRenderablesPicking(RenderSystem &render_system, const IRenderableList &renderables, const std::shared_ptr<gpu::RenderTarget> &render_target);

} // render
} // gs
