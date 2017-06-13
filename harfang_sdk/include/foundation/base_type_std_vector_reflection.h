// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include "foundation/vector.h"

namespace gs {

void RegisterBaseTypeStdVectorReflection(TypeRegistry &registry);

DeclareTypeName(std::vector<bool>, "std::vector<bool>")
DeclareTypeName(std::vector<char>, "gs::std::vector<char>")
DeclareTypeName(std::vector<short>, "std::vector<short>")
DeclareTypeName(std::vector<int>, "std::vector<int>")
DeclareTypeName(std::vector<unsigned char>, "std::vector<unsigned char>")
DeclareTypeName(std::vector<unsigned short>, "std::vector<unsigned short>")
DeclareTypeName(std::vector<unsigned int>, "std::vector<unsigned int>")
DeclareTypeName(std::vector<float>, "std::vector<float>")
DeclareTypeName(std::vector<std::string>, "std::vector<std::string>")

} // gs
