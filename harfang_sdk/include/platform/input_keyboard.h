// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "platform/input_device.h"
#include <array>

namespace gs {

class KeyboardInputDevice : public InputDevice {
public:
	KeyboardInputDevice();

	Type GetType() const override { return TypeKeyboard; }

	bool IsDown(KeyCode k) const override { return is_down[k]; }
	bool WasDown(KeyCode k) const override { return was_down[k]; }

	void ResetLastValues() override { was_down = is_down; };

protected:
	std::array<bool, KeyLast> is_down, was_down;
};

} // gs
