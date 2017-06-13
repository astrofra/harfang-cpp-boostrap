// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "platform/window_system.h"
#include <memory>

namespace gs {
namespace gpu { class Renderer; }

void ImGuiInstall(gpu::Renderer &renderer);
void ImGuiUninstall(gpu::Renderer &renderer);

void ImGuiLock();
void ImGuiUnlock();

} // gs
