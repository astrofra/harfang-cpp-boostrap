// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"

namespace gs {

namespace this_process {
/*!
	@short Set the process priority from 0 (idle) to 7 (time critical).

	0 - idle, 1 - below normal, 2 - normal, 3 - above normal, 4 - high, 5 - real time
*/
bool set_priority(uint priority);

} // this_process

/// Raise the OS timer resolution. Note that this might cause power consumption to increase.
bool os_raise_timer_resolution();
/// Restore the OS timer resolution to its default value.
bool os_restore_timer_resolution();

} // gs
