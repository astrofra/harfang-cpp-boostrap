// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/signal.h"
#include "platform/input_device.h"
#include <map>

namespace gs {

struct InputDeviceProvider {
	/// Return available device names.
	virtual std::vector<std::string> GetDevices() const = 0;
	/// Intantiate a device.
	virtual sInputDevice GetDevice(const std::string &name) = 0;
};

class InputSystem {
public:
	/// Update all system devices.
	void UpdateDevices() const;

	/// Return a list of devices available on this system.
	std::vector<std::string> GetDevices() const;
	/// Get a device from its identifier.
	sInputDevice GetDevice(const std::string &name) const;

	/// Register a direct device. GetDevice will return this device when queried for its id.
	bool RegisterDirectDevice(const std::string &name, sInputDevice device);
	/// Unregister a direct device.
	void UnregisterDirectDevice(const std::string &name);

	/// Register a device provider.
	void RegisterDeviceProvider(const std::string &name, std::unique_ptr<InputDeviceProvider> provider);

	Signal<void(const std::string &)> text_input_signal; ///< Emitted when a new character is input.

protected:
	std::map<std::string, sInputDevice> direct_devices;
	std::map<std::string, std::unique_ptr<InputDeviceProvider>> providers;

	mutable std::map<std::string, sInputDevice> devices;
};

extern global_object<InputSystem> g_input_system;

} // gs
