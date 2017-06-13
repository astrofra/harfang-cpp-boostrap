// GS Framework - Copyright 2001-2015 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"

namespace gs {
namespace core {
	
/// Metadata
class Metadata : public std::enable_shared_from_this<Metadata>, public Component {
public:
	decl_component_defaults(Metadata, "Metadata");

	Metadata();

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	comp_decl_member_get_sync_set_async(Metadata, std::string, Data, data);
};

} // core
} // gs
