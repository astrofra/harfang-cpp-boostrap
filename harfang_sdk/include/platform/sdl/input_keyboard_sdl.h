// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#ifndef	GS_SDL_KEYBOARD_INPUT_H
#define	GS_SDL_KEYBOARD_INPUT_H

#include "input/input_keyboard.h"

namespace gs {
namespace input {

/// SDL keyboard input device
struct KeyboardSDL : public Keyboard
{
	virtual	void Update();
};

}}

#endif // GS_SDL_KEYBOARD_INPUT_H
