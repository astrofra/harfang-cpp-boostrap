// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderer.h"
#include "engine/mixer.h"

namespace gs {
namespace core {

class IMovie {
public:
	enum FrameFormat {
		YUV3PlanesHalfChroma, // 3 separate planes with the U and V planes of half resolution
		ExternalOES, // external OES texture (OpenGL ES specific extension)
	};

	virtual ~IMovie() {}

	virtual bool Open(gpu::sRenderer renderer, audio::sMixer mixer, const char *filename) = 0;
	virtual bool Play() = 0;
	virtual bool Pause() = 0;
	virtual bool Close() = 0;

	virtual int64_t GetDuration() const = 0;
	virtual bool Seek(int64_t ns) = 0;
	virtual bool IsEnded() const = 0;

	virtual FrameFormat GetFormat() const = 0;
	/*!
		Return texture refs holding the movie frame for the current clock. Textures returned by
		previous calls to this function are not valid after this function returns. The textures should
	 	be presented to the viewer as soon as possible to prevent A/V desynchronization.
	 */
	virtual bool GetFrame(gpu::sTexture *planes, uint plane_count) = 0;
};

} // core
} // gs
