// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"

namespace gs {

void RegisterBaseTypeReflection(TypeRegistry &registry);

struct none {}; // dummy structure to represent the none type (as understood by most script VM)

DeclareTypeName(bool, "bool")
DeclareTypeName(char, "char")
DeclareTypeName(short, "short")
DeclareTypeName(int, "int")
DeclareTypeName(unsigned char, "unsigned char")
DeclareTypeName(unsigned short, "unsigned short")
DeclareTypeName(unsigned int, "unsigned int")
DeclareTypeName(float, "float")
DeclareTypeName(std::string, "std::string")
DeclareTypeName(none, "none")

} // gs
