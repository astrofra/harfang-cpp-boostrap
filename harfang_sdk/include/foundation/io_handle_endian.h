// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_handle.h"
#include "foundation/endian.h"

namespace gs {
namespace io {

/// IO Handle endian wrapper.
class HandleEndian {
public:
	HandleEndian(std::unique_ptr<Handle> h_, endian::Config cfg_ = endian::Little) : h(std::move(h_)), cfg(cfg_) {}

	operator bool() const { return bool(h); }

	inline Handle &GetIOHandle() const { return *h; }

	template <class T> const HandleEndian &operator<<(const T &v) {
		*h << endian::ToHost(v, cfg);
		return *this;
	}

	template <class T> const HandleEndian &operator>>(T &v) {
		*h >> v;
		endian::ToHostMem(&v, sizeof(T), cfg);
		return *this;
	}

private:
	std::unique_ptr<Handle> h;
	endian::Config cfg;
};

} // io
} // gs
