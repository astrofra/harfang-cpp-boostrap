// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_driver.h"

namespace gs {
namespace io {

/// Dispatcher I/O
class Dispatcher : public Driver {
public:
	void AddDispatch(sDriver, const char *prefix = nullptr);

	DriverCaps::Type GetCaps() const override;

	Handle *Open(const char *path, Mode mode = ModeRead) override;
	void Close(Handle &h) override;

	std::string FileHash(const char *path) override;
	bool Delete(const char *path) override { return false; }

	size_t Tell(Handle &h) override;
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef = SeekCurrent) override;

	size_t Read(Handle &h, void *data, size_t size) override;
	size_t Write(Handle &h, const void *data, size_t size) override;

	bool MkDir(const char *) override;

private:
	struct DispatchFS {
		sDriver driver;
		std::string prefix;
	};

	std::vector<sDriver> roots;
	std::vector<DispatchFS> mounts;

	sDriver Dispatch(std::string &, Mode);
};

} // io
} // gs
