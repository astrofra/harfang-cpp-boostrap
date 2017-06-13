// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "input_system/input_keyboard.h"

namespace gs {
namespace input {

/// Keyboard input X11 device
class KeyboardX11 : public Keyboard
{
public:
	void Update(Window::Handle handle) override;

	KeyboardX11();

private:
	char key_state[65536];
};

} // input
} // gs
