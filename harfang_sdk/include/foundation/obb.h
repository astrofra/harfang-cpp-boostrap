// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/matrix3.h"
#include "foundation/vector3.h"

namespace gs {

struct MinMax;

/// Oriented bounding box
struct OBB {
	OBB() {}
	OBB(const Vector3 &position, const Vector3 &scale, const Matrix3 *rotation = nullptr);

	/// Transform OBB (scaling is not supported)
	void Transform(const Matrix4 &);
	/// Return OBB transformed (scaling is not supported)
	OBB Transformed(const Matrix4 &) const;

	Vector3 position;
	Vector3 scale;

	Matrix3 rotation;
};

/// OBB from min-max.
OBB OBBFromMinMax(const MinMax &minmax);
/// Compute min-max from OBB.
MinMax MinMaxFromOBB(const OBB &obb);

} // gs
