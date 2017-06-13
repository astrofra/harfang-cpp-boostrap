// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#include "platform/input_keyboard.h"
#include "platform/input_mouse.h"

#pragma once

namespace gs {

struct AndroidMouse : MouseInputDevice {
	void Update() override;

	State current_state; // current_state as observed through the message pump
};

struct AndroidKeyboard : KeyboardInputDevice {
	void Update() override;

	std::array<bool, KeyLast> current_down;
};

KeyboardInputDevice::KeyCode AndroidKeyCodeToInputSystemKeyCode(int code);

} // gs
