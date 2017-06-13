// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include <string>
#include <vector>

namespace gs {
namespace script {

struct Callstack {
	struct Local {
		std::string name;
		TypeValue value;
	};

	struct Frame {
		std::string location; // location string formatted with as much information as possible (dependent on the VM)
		std::string file;
		uint line;
		std::vector<Local> locals;
	};

	std::vector<Frame> frames;
};

} // script
} // gs
