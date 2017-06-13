// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/plane.h"
#include "foundation/matrix4.h"
#include "foundation/matrix44.h"
#include "foundation/vector2.h"
#include <array>

namespace gs {

struct MinMax;

struct FrustumPlanes {
	Plane plane[6];
};

struct Frustum {
	enum Type { Perspective, Orthographic };

	Frustum() : type(Perspective) {}

	Type type;

	float fov_size;
	Vector2 aspect_ratio;
	float znear, zfar;

	Matrix4 world;
};

Frustum MakePerspectiveFrustum(float znear, float zfar, float fov, const Vector2 &ar, const Matrix4 &m);
Frustum MakeOrthographicFrustum(float znear, float zfar, float size, const Vector2 &ar, const Matrix4 &m);

FrustumPlanes BuildFrustumPlanes(const Frustum &frustum);
std::array<Vector3, 8> BuildFrustumVertices(const Frustum &frustum);

FrustumPlanes BuildFrustumPlanesFromProjectionMatrix(const Matrix44 &projection);

enum Visibility { Outside = 0, Inside, Clipped };

/// Return the visibility flag of a vector set against this frustum.
Visibility ClassifyPoint(const FrustumPlanes &frustum, uint count, const Vector3 *points, float distance = 0.f);
/// Return the visibility flag of a sphere against this frustum.
Visibility ClassifySphere(const FrustumPlanes &frustum, const Vector3 &origin, float radius);
/// Return the visibility flag of a minmax against this frustum.
Visibility ClassifyMinMax(const FrustumPlanes &frustum, const MinMax &minmax);

} // gs
