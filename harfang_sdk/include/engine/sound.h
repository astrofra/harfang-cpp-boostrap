// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <atomic>
#include <memory>
#include <string>

namespace gs {
namespace audio {

/// Mixer sound object
struct Sound
{
	Sound() = default;
	explicit Sound(const char *name_) : name(name_) {}

	const char *GetName() const { return name.c_str(); }

	virtual bool IsReady() const { return is_ready != 0; }

	void SetReady() { is_ready = 1; }
	void SetNotReady() { is_ready = 0; }

private:
	std::atomic<bool> is_ready;
	std::string name;
};

typedef std::shared_ptr<Sound> sSound;

} // audio
} // gs
