// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"

namespace gs {
namespace geometric {

/// Compute 2d triangle area.
float TriArea2D(float x0, float y0, float x1, float y1, float x2, float y2);

/*!
	@short	Test intersection between a ray and a plane.

	@param		a	Origin of the ray.
	@param		v	Direction of the ray.
	@param		n	Normal of the plane.
	@param		p	A point on the plane.

	@param		t	Output, the parametric 't' value of the point of
					intersection.

	@return		False if the ray is embedded in or coplanar to the plane.
				True otherwise.
*/
bool LineIntersectPlane(const Vector3 &a, const Vector3 &v, const Vector3 &n, const Vector3 &p, float &t);

/*!
	@short	Compute barycentric coordinates.
*/
void Barycentric(const Vector3 &a, const Vector3 &b, const Vector3 &c, const Vector3 &p, float &u, float &v, float &w);

/*!
	@short	Test intersection between a ray and a plane.

	@param		a	Origin of the ray.
	@param		v	Normalized direction of the ray.
	@param		c	Center of the sphere.
	@param		r	Radius of the sphere.

	@param		t	Output, the parametric 't' value of the points of
					intersection. t[0] is the closest point of
					intersection to the origin of the ray.

	@return		False if no intersection.
*/
bool LineIntersectSphere(const Vector3 &a, const Vector3 &v, const Vector3 &c, float r, float &t0, float &t1);

/*!
	@short	Determine the closest points between two lines.

	@param		a	First point on first line.
	@param		b	Second point on first line.
	@param		u	First point on second line.
	@param		v	Second point on second line.

	@param		t	Output, the parametric 't' values of the closest
					points on each line. t[0] belongs to (a;b), t[1]
					belongs to (u;v).

	@return		False if both lines are parallel.
*/
bool LineClosestPointToLine(const Vector3 &a, const Vector3 &b, const Vector3 &u, const Vector3 &v, float &t_ab, float &t_uv);

/*!
	@short	Determine the closest point to a line from a position in space.

	@param		a	First point on line.
	@param		b	Second point on line.
	@param		u	Location.
	@param		p	Output the closest point on line to u.

	@return		t	Parametric position of p on the [a;b] segment.
					If t < 0 or t > 1 then p lies outside the [a;b] segment.
*/
float LineClosestPoint(const Vector3 &a, const Vector3 &b, const Vector3 &u, Vector3 *p = nullptr);

/*!
	@short	Determine the closest point to a segment from a position in space.

	@param		a	First point on segment.
	@param		b	Second point on segment.
	@param		u	Location.
	@param		p	Output the closest point on segment to u.

	@return		t	Parametric position of p on the [a;b] segment.
*/
float SegmentClosestPoint(const Vector3 &a, const Vector3 &b, const Vector3 &u, Vector3 *p = nullptr);

} // geometric
} // gs
