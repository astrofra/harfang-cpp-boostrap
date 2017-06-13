// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector2.h"

namespace gs {
namespace gpu { struct Texture; }

void InstallDebugger();
void UninstallDebugger();

bool GetEnableDebugger();
void SetEnableDebugger(bool enable);

void DebuggerPauseScene(bool pause);

void DrawTaskSystemDebugger();
void DrawFrameProfiler();

Vector2 GetTextureDisplayRect(gpu::Texture &tex, float size);
void TextureTooltip(gpu::Texture &tex);

} // gs
