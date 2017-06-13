// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstddef>
#include <vector>

namespace gs {

template <typename T> size_t memory_usage(const std::vector<T> &v) { return v.size() * sizeof(T); }

} // gs
