// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>

namespace gs {

class guid
{
public:
	guid();
	guid(const guid &o);
	explicit guid(const char *);

	guid &operator=(const guid &);

	bool operator==(const guid &) const;
	bool operator!=(const guid &) const;
	bool operator>(const guid &) const;
	bool operator<(const guid &) const;
	bool operator>=(const guid &) const;
	bool operator<=(const guid &) const;

	std::string to_string(bool use_separator = true) const;

	inline bool is_valid() const { return (data[6] & 0xf0) == 0x40; }
	inline const unsigned char *get() const { return data; }

	static guid generate();
	static guid from_string(const char *);

private:
	unsigned char data[16];
};

} // gs

namespace std { string to_string(const gs::guid &guid); }
