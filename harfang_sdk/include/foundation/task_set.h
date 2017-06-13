// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <atomic>
#include <memory>

namespace gs {

/// Track a set of parallel tasks
class task_set
{
public:
	friend class task_system;

	inline unsigned int task_count() const { return count; }

private:
	std::atomic<unsigned int> count;
};

typedef std::shared_ptr<task_set> stask_set;

} // gs
