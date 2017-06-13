// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/script_callstack.h"
#include "engine/script_execution_context.h"
#include <string>

namespace gs {
namespace script {

class VM;

struct RuntimeError {
	std::string msg;

	std::shared_ptr<VM> vm;
	sExecutionContext execution_context;

	Callstack callstack;
};

} // script
} // gs
