// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_memory.h"

namespace gs {
namespace io {

/// I/O Crypto proxy
class Crypto : public Driver {
public:
	Crypto(Driver *, const char *key);

	DriverCaps::Type GetCaps() const override;

	Handle *Open(const char *path, Mode mode = ModeRead) override;
	void Close(Handle &h) override;

	bool Delete(const char *path) override;

	size_t Tell(Handle &h) override;
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef ref = SeekCurrent) override;

	size_t Read(Handle &h, void *out, size_t size) override;
	size_t Write(Handle &h, const void *in, size_t size) override;

	bool MkDir(const char *path) override;

private:
	std::string key;

	sDriver wrapped_io;
	std::shared_ptr<Memory> cache_driver;

	void Encrypt(std::vector<char> &data);
	void Decrypt(std::vector<char> &data);
};

} // io
} // gs
