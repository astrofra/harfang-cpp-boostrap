// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <map>
#include <string>

namespace gs {

typedef std::map<std::string, std::string> Parameters;

/// Parse a string of parameters.
Parameters ParseParameters(const std::string &parm_string);

} // gs
