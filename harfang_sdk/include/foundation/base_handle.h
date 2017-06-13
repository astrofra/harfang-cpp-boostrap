// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <cstddef>

namespace gs {

enum SeekRef { SeekStart, SeekCurrent, SeekEnd };

class BaseHandle {
public:
	virtual ~BaseHandle() {}

	virtual size_t GetSize() = 0;

	virtual size_t Rewind() = 0;
	virtual bool IsEOF() = 0;

	virtual size_t Tell() = 0;
	virtual size_t Seek(ptrdiff_t offset, SeekRef ref = SeekCurrent) = 0;

	virtual size_t Read(void *out_data, size_t size) = 0;
	virtual size_t Write(const void *in_data, size_t size) = 0;

	template <class T> bool Write(const T &v) { return this->Write(&v, sizeof(T)) == sizeof(T); }

	template <class T> T Read() {
		T v;
		this->Read(&v, sizeof(T));
		return v;
	}
};

/// Stream operator to write a value to a handle.
template <class T> BaseHandle &operator<<(BaseHandle &h, const T &v) {
	h.Write(&v, sizeof(T));
	return h;
}

/// Stream operator to read a value from a handle.
template <class T> BaseHandle &operator>>(BaseHandle &h, T &v) {
	h.Read(&v, sizeof(T));
	return h;
}

} // gs
