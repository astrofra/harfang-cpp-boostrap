// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "platform/input_device.h"

namespace gs {

class MouseInputDevice : public InputDevice {
public:
	Type GetType() const override { return TypeMouse; }

	bool IsButtonDown(ButtonCode) const override;
	bool WasButtonDown(ButtonCode) const override;

	float GetValue(InputCode) const override;
	float GetLastValue(InputCode) const override;

	void ResetLastValues() override { last_state = state; };

protected:
	struct State {
		float x = 0, y = 0;
		float wheel = 0, hwheel = 0;

		bool left_button = false;
		bool right_button = false;
		bool middle_button = false;
	};

	State state, last_state;
};

} // gs
