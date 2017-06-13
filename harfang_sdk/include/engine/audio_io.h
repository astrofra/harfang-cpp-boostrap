// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/audio_codec.h"
#include "foundation/global_object.h"
#include "foundation/vector.h"
#include <memory>

namespace gs {

/// Audio factory
class AudioIO {
public:
	/// Register an audio codec.
	void RegisterCodec(IAudioCodec *codec);
	/// Open audio data from a path.
	sAudioData Open(const char *path, const char *codec_name = nullptr);

	/// Return a comma separated list of supported extensions.
	std::string GetSupportedExt() const;

private:
	std::vector<uIAudioCodec> codecs;
};

extern global_object<AudioIO> g_audio_io;

} // gs
