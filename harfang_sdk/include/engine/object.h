// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "engine/render_geometry.h"
#include "engine/skeleton.h"

namespace gs {
namespace core {

/// Object geometry renderable
class Object : public std::enable_shared_from_this<Object>, public Component {
public:
	decl_component_defaults(Object, "Object");

	Object();
	~Object();

	comp_decl_member_get_sync_set_async_noimpl(Object, render::sGeometry, Geometry, geometry);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	ComponentState GetState() const override;

	/// Return the component renderable interface if it implements it.
	render::sIRenderable GetIRenderable() const override { return renderable; }

	/// Return the object minmax.
	MinMax GetLocalMinMax() const;

	const sSkeleton &GetSkeleton() const { return skeleton; }

	/// Return the binding bone matrix.
	bool GetBindMatrix(uint index, Matrix4 &bind_matrix) const;
	/// Update skeleton matrices.
	void UpdateSkeleton(const Transform &transform);

	void AllocateSkeleton(uint bone_count); // FIXME should be asynchronous
	void FreeSkeleton(); // FIXME should be asynchronous

	bool BindBone(uint index, sNode bone); // FIXME should be asynchronous

	bool HasSkeleton() const { return skeleton->bones.size() > 0; }
	bool IsSkinBound() const { return skeleton->bones.size() > 0 && geometry && geometry->IsReadyOrFailed() && skeleton->bones.size() == geometry->bone_bind_matrix.size(); }

	uint GetBoneCount() const { return skeleton->bones.size(); }
	const sNode &GetBone(uint index) const { return skeleton->bones[index]; }

private:
	sSkeleton skeleton;
	render::sIRenderable renderable;
};

} // core
} // gs
