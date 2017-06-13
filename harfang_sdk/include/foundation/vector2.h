// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/math.h"

namespace gs {

class Matrix3;
class Matrix4;

template <typename T, class A> class array;

/// Vector 2d template
template <class T> struct tVector2 {
	static tVector2 Zero;
	static tVector2 One;

	tVector2<T>(T a, T b) { Set(a, b); }
	tVector2<T>() { Set(0, 0); }

	inline bool operator==(const tVector2<T> &b) const { return x == b.x && y == b.y; }
	inline bool operator!=(const tVector2<T> &b) const { return x != b.x || y != b.y; }

	inline tVector2<T> &operator+=(const tVector2<T> &b) { x += b.x; y += b.y; return *this; }
	inline tVector2<T> &operator+=(const T v) { x += v; y += v; return *this; }
	inline tVector2<T> &operator-=(const tVector2<T> &b) { x -= b.x; y -= b.y; return *this; }
	inline tVector2<T> &operator-=(const T v) { x -= v; y -= v; return *this; }
	inline tVector2<T> &operator*=(const tVector2<T> &b) { x *= b.x; y *= b.y; return *this; }
	inline tVector2<T> &operator*=(const T v) { x *= v; y *= v; return *this; }
	inline tVector2<T> &operator/=(const tVector2<T> &b) { x /= b.x; y /= b.y; return *this; }
	inline tVector2<T> &operator/=(const T v) { x /= v; y /= v; return *this; }

	inline tVector2<T> operator+(const tVector2<T> &b) const { return tVector2<T>(x + b.x, y + b.y); }
	inline tVector2<T> operator+(const T v) const { return tVector2<T>(x + v, y + v); }
	inline tVector2<T> operator-(const tVector2<T> &b) const { return tVector2<T>(x - b.x, y - b.y); }
	inline tVector2<T> operator-(const T v) const { return tVector2<T>(x - v, y - v); }
	inline tVector2<T> operator*(const tVector2<T> &b) const { return tVector2<T>(x * b.x, y * b.y); }
	inline tVector2<T> operator*(const T v) const { return tVector2<T>(x * v, y * v); }
	inline tVector2<T> operator/(const tVector2<T> &b) const { return tVector2<T>(x / b.x, y / b.y); }
	inline tVector2<T> operator/(const T v) const { return tVector2<T>(x / v, y / v); }

	tVector2<T> operator*(const Matrix3 &m) const;

	tVector2<T> Min(const tVector2<T> &v) const { return tVector2<T>(x < v.x ? x : v.x, y < v.y ? y : v.y); }
	tVector2<T> Max(const tVector2<T> &v) const { return tVector2<T>(x > v.x ? x : v.x, y > v.y ? y : v.y); }

	/// Squared vector length.
	inline T Len2() const { return x * x + y * y; }
	/// Vector length.
	inline T Len() const { return T(math::Sqrt(float(Len2()))); }

	/// Dot product.
	inline T Dot(const tVector2<T> &b) const { return x * b.x + y * b.y; }

	/// Normalize this vector.
	inline void Normalize() {
		if (auto l = Len()) {
			x = x / l;
			y = y / l;
		}
	}
	/// Normalize vector.
	inline tVector2<T> Normalized() const {
		auto l = Len();
		return !l ? tVector2<T>(0, 0) : tVector2<T>(x / l, y / l);
	}

	/// Reversed vector.
	inline tVector2<T> Reversed() const { return tVector2<T>(-x, -y); }

	/// Vector squared distance.
	static inline T Dist2(const tVector2 &a, const tVector2 &b) { return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y); }
	/// Vector distance.
	static inline T Dist(const tVector2 &a, const tVector2 &b) { return T(math::Sqrt(float(Dist2(a, b)))); }

	/// Set vector 2D components.
	inline void Set(const T a, const T b) { x = a; y = b; }

	T x, y;
};

typedef tVector2<float> Vector2;
typedef tVector2<int> iVector2;

template <typename T> tVector2<T> tVector2<T>::Zero(0, 0);
template <typename T> tVector2<T> tVector2<T>::One(1, 1);

template <typename T> bool AlmostEqual(const tVector2<T> &a, const tVector2<T> &b, float e) { return types::Abs(a.x - b.x) <= e && types::Abs(a.y - b.y) <= e; }

} // gs
