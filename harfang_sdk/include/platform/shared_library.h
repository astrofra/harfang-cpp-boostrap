// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

/// Shared library interface
struct ISharedLib {
	virtual ~ISharedLib() {}

	/// Lookup for a function exported by the shared library.
	virtual void *GetFunctionPointer(const char *name) = 0;
};

/// Load a shared library.
ISharedLib *LoadSharedLibrary(const char *path);

/// Set the shared library search path.
bool SetSharedLibraryPath(const char *path);

} // gs
