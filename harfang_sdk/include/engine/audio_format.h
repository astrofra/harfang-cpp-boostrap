// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <cstdint>

namespace gs {

/// Audio format
struct AudioFormat {
	enum Encoding : uint8_t { PCM, WiiADPCM };
	enum Type : uint8_t { Integer, Float };

	AudioFormat(Encoding enc = PCM, uint8_t ch = 2, uint32_t fq = 48000, uint8_t res = 16, Type tp = Integer) : encoding(enc), channels(ch), frequency(fq), resolution(res), type(tp) {}

	Encoding encoding;
	uint8_t channels;

	uint32_t frequency;
	uint8_t resolution;

	Type type;
};

/// Get the memory usage of a number of audio sample.
inline size_t GetAudioSampleDataSize(uint sample_count, int channels, uint8_t resolution) { return (sample_count * channels * resolution) / 8; }

} // gs
