// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/math.h"
#include "foundation/rect.h"
#include "foundation/reflection.h"
#include "foundation/vector2.h"
#include <vector>

namespace gs {

struct Quaternion;
struct Matrix44;
struct Vector3;
struct Vector4;
struct MinMax;
struct Color;
struct OBB;

void RegisterFrameworkReflection(TypeRegistry &registry);

DeclareTypeName(MinMax, "gs::MinMax")
DeclareTypeName(OBB, "gs::OBB")

DeclareTypeName(math::RotationOrder, "gs::math::RotationOrder")
DeclareTypeName(math::Axis, "gs::math::Axis")

DeclareTypeName(BinaryBlob, "gs::BinaryBlob")

DeclareTypeName(Color, "gs::Color")
DeclareTypeName(std::vector<Color>, "std::vector<gs::Color>")
DeclareTypeName(Vector2, "gs::Vector2")
DeclareTypeName(std::vector<Vector2>, "std::vector<gs::Vector2>")
DeclareTypeName(iVector2, "gs::iVector2")
DeclareTypeName(std::vector<iVector2>, "std::vector<gs::iVector2>")
DeclareTypeName(Vector3, "gs::Vector3")
DeclareTypeName(std::vector<Vector3>, "std::vector<gs::Vector3>")
DeclareTypeName(Vector4, "gs::Vector4")
DeclareTypeName(std::vector<Vector4>, "std::vector<gs::Vector4>")
DeclareTypeName(Quaternion, "gs::Quaternion")
DeclareTypeName(std::vector<Quaternion>, "std::vector<gs::Quaternion>")
DeclareTypeName(Matrix3, "gs::Matrix3")
DeclareTypeName(std::vector<Matrix3>, "std::vector<gs::Matrix3>")
DeclareTypeName(Matrix4, "gs::Matrix4")
DeclareTypeName(std::vector<Matrix4>, "std::vector<gs::Matrix4>")
DeclareTypeName(Matrix44, "gs::Matrix44")
DeclareTypeName(std::vector<Matrix44>, "std::vector<gs::Matrix44>")
DeclareTypeName(fRect, "gs::fRect")
DeclareTypeName(std::vector<fRect>, "std::vector<gs::fRect>")
DeclareTypeName(iRect, "gs::iRect")
DeclareTypeName(std::vector<iRect>, "std::vector<gs::iRect>")

} // gs
