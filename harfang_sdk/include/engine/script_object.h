// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <memory>

namespace gs {
namespace script {

struct Object {
	struct Impl {
		virtual bool IsValid() const = 0;
		virtual bool IsNull() const = 0;
		virtual ~Impl() {}
	};

	Object() {}
	explicit Object(std::shared_ptr<Impl> i) : impl(std::move(i)) {}
	Object(const Object &o) : impl(o.impl) {}

	Object &operator=(const Object &o) {
		impl = o.impl;
		return *this;
	}

	inline bool IsValid() const { return impl ? impl->IsValid() : false; }
	inline bool IsNull() const { return impl ? impl->IsNull() : false; }

	inline bool IsValidAndNonNull() const { return impl ? (impl->IsValid() && !impl->IsNull()) : false; }

	inline void Release() { impl.reset(); }

	std::shared_ptr<Impl> impl;
};

} // script
} // gs
