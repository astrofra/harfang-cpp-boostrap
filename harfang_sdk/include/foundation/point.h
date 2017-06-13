// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <cstddef>

namespace gs {

/// Point 2D
template <class T> struct Point {
	Point() : x(0), y(0) {}
	Point(T ux, T uy) : x(ux), y(uy) {}

	T operator[](size_t n) const { return *(&x + n); }

	void Set(T _x, T _y) {
		x = _x;
		y = _y;
	}

	T x, y;
};

typedef Point<int> iPoint;
typedef Point<float> fPoint;

} // gs
