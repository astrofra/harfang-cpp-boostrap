// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector2.h"
#include "foundation/vector3.h"
#include "foundation/vector4.h"
#include "foundation/matrix3.h"
#include "foundation/matrix4.h"
#include "foundation/matrix44.h"
#include "foundation/rect.h"
#include "foundation/string.h"

namespace std {

string to_string(const gs::Vector2 &);
string to_string(const gs::Vector3 &);
string to_string(const gs::Vector4 &);
string to_string(const gs::Matrix3 &);
string to_string(const gs::Matrix4 &);
string to_string(const gs::Matrix44 &);
string to_string(const gs::iRect &);
string to_string(const gs::fRect &);

} // std
