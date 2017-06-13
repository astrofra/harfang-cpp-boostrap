// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include "foundation/matrix4.h"

namespace gs {

/*!
	@short Plane
	ax + by + cz + d = 0
*/
class Plane {
public:
	Plane() : n(0, 0, 0), d(0) {}
	Plane(const Vector3 &p, const Vector3 &n, const Matrix4 *transform = nullptr) { Set(p, n, transform); }

	/*!
		@short Return point distance to plane.
		Distance is signed, positive when the point is in front of the plane,
		negative otherwise.
	*/
	float DistanceToPlane(const Vector3 &p) const;

	/// Set plane from point/normal and an optional transformation matrix.
	void Set(const Vector3 &p, const Vector3 &n, const Matrix4 *transform = nullptr);
	/// Set plane three vectors and an optional transformation matrix.
	void Set(const Vector3 p[3], const Matrix4 *transform = nullptr);

	Vector3 n;
	float d;
};

} // gs
