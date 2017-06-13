// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

template <typename T> const std::string &GetTypeName() {
	static_assert(!sizeof(T), "Missing GetTypeName specialization");
	static std::string dummy;
	return dummy;
}

} // gs

#define DeclareTypeName(TYPE, NAME)                             \
	template <> inline const std::string &GetTypeName<TYPE>() { \
		static std::string name(NAME);                          \
		return name;                                            \
	}
