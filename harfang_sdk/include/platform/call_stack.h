// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>
#include <string>
#include "foundation/types.h"

namespace gs {

struct CallStackFrame {
	void *address = nullptr;

	std::string function; // function name
	std::string source; // source path

	uint line = 0;
};

struct CallStack {
	std::vector<CallStackFrame> frames;
};

void CaptureCallstack(CallStack &callstack, uint skip_frames = 0, void *context = nullptr);

} // gs

namespace std { string to_string(const gs::CallStack &callstack); }
