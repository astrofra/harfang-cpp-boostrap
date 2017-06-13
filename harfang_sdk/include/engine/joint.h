// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include "engine/component.h"
#include "engine/node.h"

#undef min
#undef max

namespace gs {
namespace core {

struct JointLimit {
	JointLimit(float mn = 0, float mx = 0) : min(mn), max(mx) {}
	bool operator==(const JointLimit &o) const { return min == o.min && max == o.max; }
	float min, max;
};

class Joint : public Component {
public:
	Joint();

	comp_decl_member_get_sync_set_async_noimpl(Joint, Vector3, Pivot, pivot);
	comp_decl_member_get_sync_set_async_noimpl(Joint, sNode, OtherBody, other_body);
	comp_decl_member_get_sync_set_async_noimpl(Joint, Vector3, OtherPivot, other_pivot);

	void *impl;

protected:
	void OnModified();
};

typedef std::shared_ptr<Joint> sJoint;

} // core
} // gs
