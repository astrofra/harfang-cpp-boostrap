// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace gs {
namespace core {

class Component;

namespace ComponentCompatibility {
	typedef int Type;
	static const Type NonCompatible = 0x00, SceneCompatible = 0x01, NodeCompatible = 0x02;
};

struct ComponentInfo {
	std::string name, aspect;
	std::function<std::shared_ptr<Component>()> make;

	ComponentCompatibility::Type compatibility = ComponentCompatibility::NonCompatible;
	bool allows_multiple_instance = false;
	
	std::vector<std::string> dependencies;
};

typedef std::shared_ptr<ComponentInfo> sComponentInfo;

// Component factory
class ComponentFactory {
public:
	/// Register a new component in the factory.
	sComponentInfo Register(const char *name, const char *aspect, std::function<std::shared_ptr<Component>()> make, ComponentCompatibility::Type, bool allows_multiple_instance = true, const char **dependencies = nullptr);
	/// Unregister a component from the factory.
	void Unregister(const char *name);

	/// Return the available component info structures.
	inline const std::vector<sComponentInfo> &GetComponentInfos() const { return component_infos; }

	/// Make a new instance of the component.
	std::shared_ptr<Component> Make(const char *name) const;
	/// Return information on the component.
	sComponentInfo GetComponentInfo(const char *name) const;

private:
	std::vector<sComponentInfo> component_infos;
};

extern ComponentFactory *g_component_factory;

void RegisterCoreComponents(ComponentFactory &factory);

} // core
} // gs
