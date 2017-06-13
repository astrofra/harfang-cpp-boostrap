// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

/// License system interface
struct ILicensing
{
	virtual ~ILicensing() {}

	// Event handler for the license system.
	virtual void onLicensingEvent(const char *) = 0;
	/// Request an update of the application license.
	virtual bool updateLicence(const char *) = 0;
};

} // gs
