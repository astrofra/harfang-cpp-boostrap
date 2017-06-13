// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/script_object.h"
#include <memory>
#include <string>

namespace gs {
namespace script {

class ExecutionContext {
public:
	enum State { StateUp, StateDown };

	virtual std::string GetDescription() const = 0;
	virtual Object GetEnv() const = 0; // return the execution context environment object

	bool IsUp() const { return state == StateUp; }
	void MarkDown() { state = StateDown; } // no code should run on this context anymore

private:
	State state = StateUp;
};

typedef std::shared_ptr<ExecutionContext> sExecutionContext;

} // script
} // gs
