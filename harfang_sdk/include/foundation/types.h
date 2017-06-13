// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstddef>

namespace gs {

typedef unsigned int uint;

namespace types {

template <class T> T inline Abs(T v) { return v < 0 ? -v : v; }

template <class T> T inline Min(T a, T b) { return a < b ? a : b; }
template <class T> T inline Max(T a, T b) { return a > b ? a : b; }

template <class T> T inline Clamp(T v, T min = 0, T max = 1) { return v < min ? min : (v > max ? max : v); }

template <class T> T inline Wrap(T v, T range_start, T range_end) {
	const T dt = range_end - range_start + 1;

	while (v < range_start)
		v += dt;
	while (v > range_end)
		v -= dt;

	return v;
}

template <class T> void inline swap(T &a, T&b) { T t = b; b = a; a = t; }

uint getPOT(uint);
bool isPOT(uint);

} // types
} // gs
