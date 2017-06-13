// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "input_system/input_mouse.h"

namespace gs {
namespace input {

/// Mouse input X11 device
class MouseX11 : public Mouse
{
public:
	MouseX11() : wheel(0), hwheel(0) {}

	bool SetValue(InputCode, float) override;

	void Update(Window::Handle handle) override;

private:
	float wheel, hwheel;
};

} // input
} // gs
