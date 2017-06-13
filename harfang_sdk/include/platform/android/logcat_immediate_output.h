// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/log.h"

namespace gs {

// Implement immediate log output to the Android logcat.
void logcat_immediate_output(const std::string &msg, const std::string &prefix, const std::string &details, LogLevel::mask_type output_mask, bool output_details);

} // gs
