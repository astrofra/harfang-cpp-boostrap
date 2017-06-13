// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/smart_median_average.h"
#include "foundation/time.h"

namespace gs {

class Clock {
public:
	Clock();

	void Reset();

	void Update();
	void Skip();

	inline time_t Get() const { return current; }
	inline time_t GetDelta() const { return dt; }

private:
	time_t last = 0, current = 0;
	time_t dt = 0, dt_error = 0;

	SmartMedianAverage<time_t> dt_history;
};

} // gs
