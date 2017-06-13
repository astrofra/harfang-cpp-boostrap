// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

struct log_tail {
public:
	static const int size = 8192;

	log_tail();

	/// Write to tail content.
	void write(const std::string &msg);
	/// Get static tail content.
	inline const char *get() const { return tail; }

private:
	char tail[size + 1];
	size_t cursor;
};

} // gs
