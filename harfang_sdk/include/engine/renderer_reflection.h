// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include <memory>

namespace gs {

namespace gpu {
class Renderer;
struct Texture;
struct RenderTarget;
} // gpu

void RegisterRendererReflection(TypeRegistry &registry);

DeclareTypeName(gpu::Renderer, "gs::gpu::Renderer")
DeclareTypeName(std::shared_ptr<gpu::Renderer>, "gs::gpu::sRenderer")

DeclareTypeName(gpu::RenderTarget, "gs::gpu::RenderTarget")
DeclareTypeName(std::shared_ptr<gpu::RenderTarget>, "gs::gpu::sRenderTarget")

DeclareTypeName(gpu::Texture, "gs::gpu::Texture")
DeclareTypeName(std::shared_ptr<gpu::Texture>, "gs::gpu::sTexture")

} // gs
