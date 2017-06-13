// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#include "foundation/frustum.h"

namespace gs {
namespace render {

class RenderSystem;

void DrawFrustum(RenderSystem *render_system, const Frustum &frustum, Color color);
void DrawMinMax(RenderSystem *render_system, const uint count, const MinMax *mm, Color color);
void DrawCross(RenderSystem *render_system, const uint count, const Vector3 *pos, float size, Color color);
void DrawSphere(RenderSystem *render_system, const uint count, const Vector3 *pos, const float *radius, Color color);
void DrawCapsule(RenderSystem *render_system, const uint count, const Vector3 *pos, const float *radius, const float *half_length, Color color);

} // render
} // gs
