// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <X11/Xlib.h>
#include "X11/Xutil.h"

#undef Button1
#undef Button2
#undef Button3
#undef Button4
#undef Button5

#include "input_system/input_system.h"
#include "input_system/input_mouse.h"
#include "input_system/input_keyboard.h"

namespace gs {
namespace input {

/// Input system X11
class SystemX11 : public System {
public:
	SystemX11();

	/// Set window handle.
	void SetWindowHandle(Window::Handle handle) override;

	void Update() override;

	/// Return a list of devices available on this system.
	void GetDevices(vector<DeviceDesc> &devices) const override;
	/// Get device.
	Device *GetDevice(const char *name) override;

private:
	Window::Handle window;

	shared_ptr<Device> mouse, keyboard;
};

} // input
} // gs
