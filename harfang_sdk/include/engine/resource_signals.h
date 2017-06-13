// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include <functional>
#include <map>
#include <mutex>
#include <vector>

namespace gs {
namespace gpu {

struct Resource;

struct ResourceSignals {
	std::mutex on_resource_ready_mutex;
	std::map<const Resource *, std::vector<std::function<void()>>> on_resource_ready;
};

extern global_object<ResourceSignals> g_resource_signals;

} // gpu
} // gs
