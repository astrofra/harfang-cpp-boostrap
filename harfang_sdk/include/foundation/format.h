// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/string.h"
#include "foundation/types.h"
#include <sstream>

namespace std {

string to_string(const void *p);

inline string to_string(const string &v) { return v; }
inline string to_string(const char *v) { return v; }

} // std

namespace gs {

struct format {
	explicit format(const char *text_) : text(text_), i(1) {}

	operator const char *() const { return text.c_str(); }
	const std::string &str() const { return text; }

	template <typename T> format &arg(const T &v) {
		std::string token = "%";
		token += std::to_string(i++);
		replace_all(text, token, std::to_string(v));
		return *this;
	}

private:
	std::string text;
	int i;
};

} // gs
