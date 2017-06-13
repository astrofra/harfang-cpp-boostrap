// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#ifndef	GS_INPUT_SDL_SYSTEM_H
#define	GS_INPUT_SDL_SYSTEM_H

#include "input/input_system.h"
#include "input/input_keyboard.h"

namespace gs {
namespace input {

/// SDL input system
class SDLSystem : public System
{
	shared_ptr <Device> null_device, mouse, keyboard;

public:

	virtual	void Update();

	/// Return a list of devices available on this system.
	virtual	bool GetDeviceList(StringList &, Device::Type = Device::Type_Any) const;
	/// Get device.
	virtual	Device *GetDevice(const char *name);

	/// Touch event.
	void RegisterTouchEvent(int index, float x, float y, float w);

	SDLSystem();
};

}}

#endif // GS_INPUT_SDL_SYSTEM_H
