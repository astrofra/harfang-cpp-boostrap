// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include "engine/component.h"

namespace gs {

namespace render {
class Geometry;
struct IRenderable;
} // render

struct IDocumentReader;
struct IDocumentWriter;

namespace core {

/// Decorator component
class Decorator : public std::enable_shared_from_this<Decorator>, public Component {
public:
	decl_component_defaults(Decorator, "Decorator");

	Decorator();

	comp_decl_member_get_sync_set_async_noimpl_novar(Decorator, std::shared_ptr<render::Geometry>, Geometry);

	comp_decl_member_get_sync_set_async_noimpl_novar(Decorator, float, Range);
	comp_decl_member_get_sync_set_async_noimpl_novar(Decorator, bool, Decimate);
	comp_decl_member_get_sync_set_async_noimpl_novar(Decorator, float, DecimationRangeStart);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	/*
		Note: This function can safely be called during rendering but should not
		be called from two different threads at the same time.
	*/
	void AddInstance(const Matrix4 &world);

	ComponentState GetState() const override;

	std::shared_ptr<render::IRenderable> GetIRenderable() const override { return renderable; }

	mutable std::string data_path;

	bool SaveData(const char *path) const;
	bool LoadData(const char *path);

private:
	std::shared_ptr<render::IRenderable> renderable;

	std::vector<Matrix4> queued_instances;
	void commit_AddInstance();
};

} // core
} // gs
