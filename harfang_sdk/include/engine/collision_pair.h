// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"
#include "engine/node.h"

namespace gs {
namespace core {

struct CollisionPair {
	CollisionPair() : contact_count(0) {}
	CollisionPair(sNode a_, sNode b_) : a(std::move(a_)), b(std::move(b_)), contact_count(0) {}

	sNode a, b;

	struct Contact {
		Vector3 p, n;
	};

	uint8_t contact_count;
	Contact contact[4];
};

} // core
} // gs
