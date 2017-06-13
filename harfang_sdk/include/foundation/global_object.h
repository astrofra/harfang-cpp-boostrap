// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/assert.h"

template <typename T> class global_object {
public:
	bool is_set() const { return i; }

	inline T &get() const {
		__ASSERT__(i != nullptr);
		return *i;
	}

	void set(T *o) {
		__ASSERT__(i == nullptr);
		i = o;
	}

	inline operator bool() const { return bool(i); }

private:
	T *i;
};
