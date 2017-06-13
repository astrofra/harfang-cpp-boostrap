// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/matrix44.h"
#include "foundation/vector2.h"

namespace gs {

float ZoomFactorToFov(float zoom_factor);
float FovToZoomFactor(float fov);

Matrix44 ComputeOrthographicProjectionMatrix(float znear, float zfar, float size, const Vector2 &aspect_ratio);
Matrix44 ComputePerspectiveProjectionMatrix(float znear, float zfar, float zoom_factor, const Vector2 &aspect_ratio);

} // gs
