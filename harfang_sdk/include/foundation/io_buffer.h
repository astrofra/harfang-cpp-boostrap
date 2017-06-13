// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_driver.h"

namespace gs {
namespace io {

/*!
	@short Buffered I/O filesystem wrapper
	Implements a transparent read/write buffer on top of another filesystem.
*/
class Buffer : public Driver
{
public:
	Buffer(sDriver driver, size_t read_buffer_size = 4096, size_t write_buffer_size = 4096);

	DriverCaps::Type GetCaps() const override;

	Handle *Open(const char *path, Mode mode = ModeRead) override;
	void Close(Handle &) override;

	std::string FileHash(const char *path) override;
	bool Delete(const char *path) override;

	size_t Tell(Handle &h) override;
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef = SeekCurrent) override;
	size_t Size(Handle &h) override;

	bool IsEOF(Handle &h) override;

	size_t Read(Handle &h, void *, size_t) override;
	size_t Write(Handle &h, const void *, size_t) override;

	bool MkDir(const char *path) override;

private:
	sDriver driver;
	size_t read_buffer_size, write_buffer_size;
};

} // io
} // gs
