// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

struct LogScope {
	LogScope(const char *enter, const char *exit);
	~LogScope();

private:
	std::string exit;
};

} // gs
