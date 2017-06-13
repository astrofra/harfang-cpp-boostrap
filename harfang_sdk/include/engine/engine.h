// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/renderer.h"
#include "foundation/time.h"
#include "foundation/signal.h"

namespace gs {
namespace core {

struct Engine {
	Signal<void(gpu::Renderer &)> new_renderer_signal, delete_renderer_signal;

	Signal<void()> end_frame_signal; // end of frame signaled
	uint64_t last_frame_duration = 0, last_frame_end = 0;
};

extern global_object<Engine> g_engine;

// post_init_signal is used before g_engine is initialized
extern Signal<void()> post_init_signal;

/// Return the executable path.
const std::string &GetExecutablePath();

/// Initialize framework.
void Init(const char *executable_path = "");
/// Uninitialize framework.
void Uninit();

/// Mark the end of the current frame.
void EndFrame();
/// Get the last frame duration in nanoseconds.
time_t GetLastFrameDuration();
/// Reset the last frame duration.
void ResetLastFrameDuration();

} // core
} // gs
