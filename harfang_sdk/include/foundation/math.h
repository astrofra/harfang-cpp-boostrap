// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <cstdint>

namespace gs {
namespace math {

static const float Pi = 3.1415926535f;

static const float HalfPi = Pi / 2.f;
static const float TwoPi = Pi * 2.f;

/// Euler angles rotation order.
enum RotationOrder : uint8_t {
	RotationOrderZYX,
	RotationOrderYZX,
	RotationOrderZXY,
	RotationOrderXZY,
	RotationOrderYXZ,
	RotationOrderXYZ,
	RotationOrderXY,
	RotationOrder_Default = RotationOrderYXZ // Y then X then Z
};

enum Axis : uint8_t { AxisX, AxisY, AxisZ, AxisNone };

void Init();

/// Return the reverse rotation order from a given input order.
RotationOrder ReverseRotationOrder(RotationOrder r);

float Sqrt(float v);

float TestEqual(float a, float b, float e = 0.000001f);
bool EqualZero(float v, float e = 0.000001f);

float Pow(float v, float exp);

float Ceil(float);
float Floor(float);
float Mod(float);

float Frac(float);

float RangeAdjust(float v, float old_min, float old_max, float new_min, float new_max);

float Quantize(float v, float q);

float Sin(float);
float ASin(float);
float Cos(float);
float ACos(float);
float Tan(float);
float ATan(float);

bool IsFinite(float);

template <typename T> T LinearInterpolate(T y0, T y1, float t) { return y0 + (y1 - y0) * t; }

template <typename T> T CosineInterpolate(T y0, T y1, float t) {
	float t2 = (1.f - Cos(t * Pi)) / 2.f;
	return y0 * (1.f - t2) + y1 * t2;
}

template <typename T> T CubicInterpolate(T y0, T y1, T y2, T y3, float t) {
	float t2 = t * t;
	T a0 = y3 - y2 - y0 + y1, a1 = y0 - y1 - a0, a2 = y2 - y0, a3 = y1;
	return a0 * t * t2 + a1 * t2 + a2 * t + a3;
}

/*
	tension: 1 is high, 0 normal, -1 is low
	bias: 0 is even, positive is towards first segment, negative towards the other
*/
template <typename T> T HermiteInterpolate(T y0, T y1, T y2, T y3, float t, float tension, float bias) {
	float t2 = t * t;
	float t3 = t2 * t;
	T t0 = (y1 - y0) * (1.f + bias) * (1.f - tension) / 2.f;
	t0 += (y2 - y1) * (1.f - bias) * (1.f - tension) / 2.f;
	T t1 = (y2 - y1) * (1.f + bias) * (1.f - tension) / 2.f;
	t1 += (y3 - y2) * (1.f - bias) * (1.f - tension) / 2.f;
	float a0 = 2.f * t3 - 3 * t2 + 1.f;
	float a1 = t3 - 2.f * t2 + t;
	float a2 = t3 - t2;
	float a3 = -2.f * t3 + 3.f * t2;
	return a0 * y1 + a1 * t0 + a2 * t1 + a3 * y2;
}

template <class T> T LinearInterpolateArray(uint count, const T *values, float t) {
	float s = t * (count - 1);
	uint lo = uint(s), hi = lo + 1;

	lo = types::Clamp<uint>(lo, 0, count - 1);
	hi = types::Clamp<uint>(hi, 0, count - 1);

	return LinearInterpolate(values[lo], values[hi], s - lo);
}

template <typename T> T Min(const T &a, const T &b) { return a < b ? a : b; }
template <typename T> T Max(const T &a, const T &b) { return a > b ? a : b; }

} // math
} // gs
