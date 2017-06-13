// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/rect.h"
#include "foundation/signal.h"
#include "foundation/string.h"
#include <array>
#include <map>

namespace gs {

struct Monitor {
	std::array<int8_t, 64> data{};
}; // 64 bytes

/// Return the monitor rect.
iRect GetMonitorRect(const Monitor &monitor);
/// Return true if the monitor is set as primary.
bool IsPrimaryMonitor(const Monitor &monitor);

//
struct Surface {
	std::array<int8_t, 32> data{};
}; // 32 bytes

extern Surface NoSurface;

bool operator==(const Surface &a, const Surface &b);

//
struct Window {
	enum Visibility { Windowed, Undecorated, Fullscreen, Hidden, FullscreenMonitor1, FullscreenMonitor2, FullscreenMonitor3 };

	std::array<int8_t, 32> data{};
}; // 32 bytes

bool operator==(const Window &a, const Window &b);

/// Must be called from the main thread.
void WindowSystemInit();

/// Create a new window.
Window NewWindow(int width, int height, int bpp = 32, Window::Visibility visibility = Window::Windowed);
/// Wrap a foreign window native handle in a new window.
Window NewWindowFrom(void *handle);

/// Return the window native handle.
void *GetWindowHandle(const Window &w);

/// Pool window events.
bool UpdateWindow(const Window &w);

/// Destroy a window.
bool DestroyWindow(Window &w);

/// Get the window client size.
bool GetWindowClientSize(const Window &w, int &width, int &height);
/// Set the window client size.
bool SetWindowClientSize(const Window &w, int width, int height);

/// Get the window title as an UTF-8 string.
bool GetWindowTitle(const Window &w, std::string &title);
/// Set the window title from an UTF-8 string.
bool SetWindowTitle(const Window &w, const std::string &title);

/// Return true if the provided window has input focus.
bool WindowHasFocus(const Window &w);

/// Return the system handle to the window currently in focus.
Window GetWindowInFocus();

/// Get a list of monitors connected to the system.
std::vector<Monitor> GetMonitors();

/// Get the window position
iVector2 GetWindowPos(const Window &w);
/// Set the window position
bool SetWindowPos(const Window &w, const iVector2 v);

/// Window system shared state.
struct WindowSystem {
	Window window_in_focus;

	Signal<void(const Window &)> new_window_signal;
	Signal<void(const Window &, bool)> window_focus_signal;
	Signal<void(const Window &)> close_window_signal;

#if ANDROID
	void *display = nullptr;
	void *main_window_handle = nullptr;
#elif __linux__
	void *display = nullptr;
	int screen = 0;
#endif
};

extern global_object<WindowSystem> g_window_system;

} // gs
