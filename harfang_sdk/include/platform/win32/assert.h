// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs {

// Provide support for Win32 message box based assertion.
void win32_trigger_assert(const char *source, int line, const char *function, const char *condition, const char *message);

} // gs
