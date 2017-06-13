// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

/*!
	@short Return a unique temporary filename.

	@warning This function can race between the name creation and the actual
	file creation.
*/
std::string GetTempFilename(const char *prefix);

/// Open a file dialog
bool OpenFileDialog(const char *title, std::string filter, std::string &OUTPUT, const char *initial_dir = nullptr);
/// Open a save file dialog
bool SaveFileDialog(const char *title, std::string filter, std::string &OUTPUT, const char *initial_dir = nullptr);

/// Platform specific initialization.
bool InitPlatform();

} // gs
