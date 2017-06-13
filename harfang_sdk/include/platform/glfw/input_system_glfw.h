// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "GLFW/glfw3.h"
#include "input/input_system.h"
#include "input/input_mouse.h"
#include "input/input_keyboard.h"

namespace gs {
namespace input {

/// Input system GLFW
class SystemGLFW : public System
{
public:
	SystemGLFW();
	~SystemGLFW();

	inline Device *GetMouse() const { return nullptr; }
	inline Device *GetKeyboard() const { return nullptr; }

	/// Return the window handle type.
	const char *GetType() const override { return "GLFW"; }
	/// Set window handle.
	void SetWindow(void *h) override { window = reinterpret_cast<GLFWwindow *>(h); }

	void Update() override;

	/// Return a list of devices available on this system.
	void GetDevices(vector<DeviceDesc> &devices) const override;
	/// Get device.
	Device *GetDevice(const char *name) override;

private:
	GLFWwindow *window;

	shared_ptr<Device> mouse, keyboard;
};

} // input
} // gs
