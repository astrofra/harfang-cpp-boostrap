// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/task_set.h"

namespace gs {

typedef char task_affinity;
typedef char task_priority;

static const task_affinity any_task_worker = -1;
static const task_priority default_task_priority = 0;

class task
{
public:
	friend class task_system;

	virtual void run() = 0;

	const stask_set &get_task_set() const { return set; }

private:
	stask_set set;
	task_affinity aff = any_task_worker;
	task_priority prt = default_task_priority;
};

typedef std::shared_ptr<task> stask;

} // gs
