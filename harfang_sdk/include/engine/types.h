// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstdint>

#if defined(ANDROID) || TARGET_OS_IPHONE
//#define EGL_HALF_FLOAT_SUPPORT
#endif

#ifdef EGL_HALF_FLOAT_SUPPORT
	typedef unsigned short hfloat;
	#define EGL_HFLOAT GL_HALF_FLOAT_OES
	#define EGL_HFLOAT_SIZE 2
#else
	typedef float hfloat;
	#define EGL_HFLOAT GL_FLOAT
	#define EGL_HFLOAT_SIZE 4
#endif

namespace gs {
namespace gpu {

enum PrimitiveType : uint8_t { PrimitiveLine, PrimitiveTriangle, PrimitivePoint, PrimitiveLast };

/// Convert float to half-float.
hfloat FloatToHFloat(float f);
/// Convert float to half-float.
float HFloatToFloat(hfloat hf);

} // gpu
} // gs
