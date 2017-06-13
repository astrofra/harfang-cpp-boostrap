// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"

namespace gs {
namespace render { class RenderSystem; }
namespace core {

/*!
	@short Scene overlay component.
	Base class for scene overlay components used to draw UI or custom debug
	elements.
*/
class SceneOverlay : public Component {
public:
	/// Called before the scene update starts.
	virtual void PreUpdate(render::RenderSystem &render_system) {}
	/// Draw the render overlay, this method is called from the render thread.
	virtual void Draw(render::RenderSystem &render_system) = 0;
	/// Called after the scene complete.
	virtual void Clear(render::RenderSystem &render_system) = 0;
};

} // core
} // gs
