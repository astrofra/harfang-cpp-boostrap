// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/math.h"

namespace gs {

class Matrix3;
class Matrix4;
struct Vector3;
struct Color;

template <class T> struct tVector2;
template <class T, class A> class array;

/// 4-Component vector
struct Vector4 {
	static const Vector4 Zero;
	static const Vector4 One;

	Vector4() {} //-V730
	explicit Vector4(const Color &);
	explicit Vector4(const Vector3 &);
	explicit Vector4(const tVector2<int> &);
	explicit Vector4(const tVector2<float> &);
	explicit Vector4(const float *v) { Set(v); }
	Vector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}

	inline bool operator==(const Vector4 &b) const { return x == b.x && y == b.y && z == b.z; }
	inline bool operator!=(const Vector4 &b) const { return x != b.x || y != b.y || z != b.z; }

	Vector4 &operator+=(const Vector4 &b) { x += b.x; y += b.y; z += b.z; w += b.w; return *this; }
	Vector4 &operator+=(const float k) { x += k; y += k; z += k; w += k; return *this; }
	Vector4 &operator-=(const Vector4 &b) { x -= b.x; y -= b.y; z -= b.z; w -= b.w; return *this; }
	Vector4 &operator-=(const float k) { x -= k; y -= k; z -= k; w -= k; return *this; }
	Vector4 &operator*=(const Vector4 &b) { x *= b.x; y *= b.y; z *= b.z; w *= b.w; return *this; }
	Vector4 &operator*=(const float k) { x *= k; y *= k; z *= k; w *= k; return *this; }
	Vector4 &operator/=(const Vector4 &b) { x /= b.x; y /= b.y; z /= b.z; w /= b.w; return *this; }
	Vector4 &operator/=(const float k) { float k_ = k ? 1 / k : 0; x *= k_; y *= k_; z *= k_; w *= k_; return *this; }

	Vector4 operator+(const Vector4 &b) const { return Vector4(x + b.x, y + b.y, z + b.z, w + b.w); }
	Vector4 operator+(const float v) const { return Vector4(x + v, y + v, z + v, w + v); }
	Vector4 operator-(const Vector4 &b) const { return Vector4(x - b.x, y - b.y, z - b.z, w - b.w); }
	Vector4 operator-(const float v) const { return Vector4(x - v, y - v, z - v, w - v); }
	Vector4 operator*(const Vector4 &b) const { return Vector4(x * b.x, y * b.y, z * b.z, w * b.w); }
	Vector4 operator*(const float v) const { return Vector4(x * v, y * v, z * v, w * v); }
	Vector4 operator/(const Vector4 &b) const { return Vector4(x / b.x, y / b.y, z / b.z, w / b.w); }
	Vector4 operator/(const float v) const { float i = v ? 1.f / v : 0.f; return Vector4(x * i, y * i, z * i, w * i); }

	void operator*=(const Matrix4 &);
	Vector4 operator*(const Matrix4 &) const;

	inline void Set(float a = 0, float b = 0, float c = 0, float d = 1) { x = a; y = b; z = c; w = d; }
	inline void Set(const float *v) { x = v[0]; y = v[1]; z = v[2]; w = v[3]; }

	inline float operator[](size_t n) const { return (&x)[n]; }
	inline float &operator[](size_t n) { return (&x)[n]; }

	inline Vector4 Abs() const { return Vector4(x > 0 ? x : -x, y > 0 ? y : -y, z > 0 ? z : -z, w > 0 ? w : -w); }

	inline Vector4 Normalized() const
	{
		const float l = math::Sqrt(x * x + y * y + z * z + w * w);
		return l > 0.f ? *this / l : *this;
	}

	float x, y, z, w;
};

} // gs
