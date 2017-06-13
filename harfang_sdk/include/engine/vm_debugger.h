// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/script_execution_context.h"
#include "engine/vm.h"

namespace gs {
namespace render { class RenderSystem; }

void InstallVMDebugger();
void UninstallVMDebugger();

void DrawVMDebugger(render::RenderSystem &render_system);

void NewExecutionContextInspector(script::sVM vm, script::ExecutionContext &exec_ctx);

} // gs
