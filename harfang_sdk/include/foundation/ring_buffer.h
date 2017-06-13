// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>

namespace gs {

/// Circular ring buffer
template <class T> class ring_buffer
{
public:
	/// Get the maximum number of element in buffer.
	inline uint size() const { return buffer.size(); }

	/// Number of object left to put in the buffer.
	inline uint GetFree() const { return buffer.size() - usage; }
	/// Number of object available to get from the buffer.
	inline uint GetUsage() const { return usage; }

	/// Increment the put pointer, returns true when successful.
	bool Produce()
	{
		if (usage == buffer.size())
			return false;

		put = (put + 1) % buffer.size();
		usage++;

		return true;
	}

	/// Increment the get pointer, returns true when successful.
	bool Consume()
	{
		if (usage == 0)
			return false;

		get = (get + 1) % buffer.size();
		usage--;

		return true;
	}

	/// Retrieve the object at the current get pointer.
	inline T &CurrentGet() { return buffer[get]; }
	/// Retrieve the object at the current put pointer.
	inline T &CurrentPut() { return buffer[put]; }

	bool Allocate(uint count)
	{
		put = get = usage = 0;
		return buffer.resize(count);
	}

private:
	std::vector<T> buffer;
	uint put = 0, get = 0, usage = 0;
};

} // gs
