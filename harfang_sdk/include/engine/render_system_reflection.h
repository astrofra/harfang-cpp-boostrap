// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include <memory>

namespace gs {

namespace render {
struct IRenderable;
class SurfaceShader;
class Material;
class Geometry;
class RenderSystem;
} // render

void RegisterRenderSystemReflection(TypeRegistry &registry);

DeclareTypeName(render::IRenderable, "gs::render::Renderable")
DeclareTypeName(std::shared_ptr<render::IRenderable>, "gs::render::sRenderable")

DeclareTypeName(render::SurfaceShader, "gs::render::SurfaceShader")
DeclareTypeName(std::shared_ptr<render::SurfaceShader>, "gs::render::sSurfaceShader")

DeclareTypeName(render::Material, "gs::render::Material")
DeclareTypeName(std::shared_ptr<render::Material>, "gs::render::sMaterial")

DeclareTypeName(render::Geometry, "gs::render::Geometry")
DeclareTypeName(std::shared_ptr<render::Geometry>, "gs::render::sGeometry")

DeclareTypeName(render::RenderSystem, "gs::render::RenderSystem")
DeclareTypeName(std::shared_ptr<render::RenderSystem>, "gs::render::sRenderSystem")

} // gs
