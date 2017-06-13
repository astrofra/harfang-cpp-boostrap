// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/picture.h"
#include "foundation/reflection.h"
#include <memory>

namespace gs {
namespace core {

struct TangentFrame;

class Geometry;
struct GeometrySkin;

struct Polygon;

struct Shader;
enum ShaderType : uint8_t;
struct ShaderValue;

struct Material;

enum TextureUV : uint8_t;
enum TextureFilter : uint8_t;
struct TextureUnitConfig;

} // core

void RegisterCoreReflection(TypeRegistry &registry);

DeclareTypeName(Picture, "gs::Picture")
DeclareTypeName(sPicture, "gs::sPicture")

DeclareTypeName(core::TangentFrame, "gs::core::TangentFrame")
DeclareTypeName(std::vector<core::TangentFrame>, "std::vector<gs::core::TangentFrame>")

DeclareTypeName(core::Geometry, "gs::core::Geometry")
DeclareTypeName(std::shared_ptr<core::Geometry>, "gs::core::sGeometry")
DeclareTypeName(core::GeometrySkin, "gs::core::GeometrySkin")

DeclareTypeName(core::Polygon, "gs::core::Polygon")

DeclareTypeName(core::Shader, "gs::core::Shader")
DeclareTypeName(std::shared_ptr<core::Shader>, "gs::core::sShader")
DeclareTypeName(core::ShaderType, "gs::core::ShaderType")
DeclareTypeName(core::ShaderValue, "gs::core::ShaderValue")

DeclareTypeName(core::Material, "gs::core::Material")
DeclareTypeName(std::shared_ptr<core::Material>, "gs::core::sMaterial")

DeclareTypeName(core::TextureUV, "gs::core::TextureUV")
DeclareTypeName(core::TextureFilter, "gs::core::TextureFilter")
DeclareTypeName(core::TextureUnitConfig, "gs::core::TextureUnitConfig")

} // gs
