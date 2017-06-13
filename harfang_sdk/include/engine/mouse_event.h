// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {
namespace core {

enum MouseEventType { MouseEventNone = 0, MouseEventMove = 1, MouseEventClick = 2 };
enum MouseEventButton { MouseEventNoButton = 0, MouseEventLeftButton = 1, MouseEventRightButton = 2, MouseEventMiddleButton = 4 };

struct MouseState {
	uint8_t buttons = MouseEventNoButton;
	float x = 0, y = 0, wheel = 0;
};

struct MouseEvent {
	uint8_t type = MouseEventNone;
	MouseState state, last_state;
};

} // core
} // gs
