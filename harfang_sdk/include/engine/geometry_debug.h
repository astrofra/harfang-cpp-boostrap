// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

namespace gs { struct Color;
namespace render { class RenderSystem; }
namespace core {

class Geometry;

void DrawGeometryNormals(render::RenderSystem &sys, const Geometry &geo, const Color &N_color, float size = 0.1f);
void DrawGeometryTangents(render::RenderSystem &sys, const Geometry &geo, const Color &T_color, const Color &B_color, float size = 0.1f);

} // core
} // gs