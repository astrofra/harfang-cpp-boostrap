// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_handle.h"

namespace gs {
namespace io {

class HandleSegment : public Handle
{
public:
	HandleSegment(Handle *h, size_t o, size_t s) : Handle(nullptr), handle(h), offset(o), size(s), cursor(0) {}

	size_t GetSize() override { return size; }

	size_t Tell() override { return cursor; }
	size_t Seek(ptrdiff_t, SeekRef = SeekCurrent) override;

	size_t Read(void *, size_t) override;
	size_t Write(const void *, size_t) override;

private:
	Handle *handle;
	size_t offset, size;
	size_t cursor;
};

} // io
} // gs
