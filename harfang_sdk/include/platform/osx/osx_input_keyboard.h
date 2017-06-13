// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "input_system/input_keyboard.h"

namespace gs {
namespace input {

/// Keyboard input OSX device
class KeyboardOSX : public Keyboard
{
public:
	void Update(Window::Handle handle) override;
};

} // input
} // gs
