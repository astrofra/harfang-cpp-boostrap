// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/color.h"
#include "engine/resource.h"
#include "engine/component.h"

namespace gs {
namespace core {

/// Scene environment component
class Environment : public std::enable_shared_from_this<Environment>, public Component {
public:
	decl_component_defaults(Environment, "Environment");

	Environment();

	comp_decl_member_get_sync_set_async_validated(Environment, float, TimeOfDay, time_of_day, ClampToZeroOne);

	comp_decl_member_get_sync_set_async(Environment, Color, BackgroundColor, background_color);

	comp_decl_member_get_sync_set_async_validated(Environment, float, AmbientIntensity, ambient_intensity, ClampToZero);
	comp_decl_member_get_sync_set_async(Environment, Color, AmbientColor, ambient_color);

	comp_decl_member_get_sync_set_async(Environment, Color, FogColor, fog_color);
	comp_decl_member_get_sync_set_async_validated(Environment, float, FogNear, fog_near, ClampToZero);
	comp_decl_member_get_sync_set_async_validated(Environment, float, FogFar, fog_far, ClampToZero);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }
};

typedef std::shared_ptr<Environment> sEnvironment;

} // core
} // gs
