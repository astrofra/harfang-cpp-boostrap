// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/string.h"
#include "engine/component.h"
#include "engine/group.h"

namespace gs {
namespace core {

/// Scene instance.
class Instance : public std::enable_shared_from_this<Instance>, public Component {
public:
	decl_component_defaults(Instance, "Instance");

	Instance();

	comp_decl_member_get_sync_set_async_noimpl(Instance, std::string, Path, path);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	ComponentState GetState() const override;

	sGroup group;

private:
	friend void InstanceSetInternalComponentState(Instance &instance, ComponentState state);

	ComponentState state;
};

typedef std::shared_ptr<Instance> sInstance;

} // core
} // gs
