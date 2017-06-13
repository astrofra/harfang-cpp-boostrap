// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>
#include <vector>

namespace gs {

struct NamedParm {
	NamedParm() = default;
	NamedParm(NamedParm &&p) : name(std::move(p.name)), value(std::move(p.value)) {}
	std::string name, value;
};

typedef std::vector<NamedParm> NamedParmArray;

/*!
	@short Clean a parameter name or value string.

	Strip the string left and right of empty characters, and normalize end of
	line characters.
*/
void CleanNamedParmString(std::string &str);

/*!
	@short Parse a string of named parameters

	The string is expected to embed parameters in the following format:
	<name_0:value_0>,<name_1:value_1>,...

	@note The name and value will be cleaned when extracted.
*/
NamedParmArray ParseNamedParmString(const std::string &parm_str);

} // gs
