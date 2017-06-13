// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#ifndef	GS_SDL_MOUSE_INPUT_H
#define	GS_SDL_MOUSE_INPUT_H

#include "input/input_mouse.h"

namespace gs {
namespace input {

/// SDL mouse input device
class MouseSDL : public Mouse
{
public:

	enum Button
	{
		LeftButton		=	0,
		MiddleButton,
		RightButton
	};

	bool SetButtonState(Button, bool state);
	bool SetValue(InputCode, float);

	virtual	void Update();
};

}}

#endif // GS_SDL_MOUSE_INPUT_H
