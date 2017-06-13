// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/audio_data.h"
#include "foundation/types.h"

namespace gs {

/// Audio codec base class.
struct IAudioCodec {
	virtual ~IAudioCodec() {}

	/// Get the codec name.
	virtual const char *GetName() = 0;
	/// Open audio data.
	virtual sAudioData Open(const char *path) = 0;

	/// Return a comma separated list of supported extensions.
	virtual const char *GetSupportedExt() const = 0;
};

typedef std::unique_ptr<IAudioCodec> uIAudioCodec;

} // gs
