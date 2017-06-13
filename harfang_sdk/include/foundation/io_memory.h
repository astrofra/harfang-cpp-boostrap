// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>
#include <memory>
#include <mutex>

#include "foundation/io_driver.h"

namespace gs {
namespace io {

class MemoryFile
{
public:
	friend class Memory;

	inline const std::string &GetPath() const { return path; }
	inline const std::vector<char> &GetData() const { return data; }
	inline size_t GetSize() const { return size; }

private:
	std::string path;
	std::vector<char> data;
	size_t size; // might be != data.GetSize()

	explicit MemoryFile(const char *_path = nullptr) : path(_path), size(0) {}
};

typedef std::vector<std::shared_ptr<MemoryFile>> MemoryFat;

/// Memory I/O
class Memory : public Driver
{
public:
	/// Return the system file allocation table.
	inline const MemoryFat &GetFat() const { return fat; }
	/// Return the system table of content.
	std::vector<std::string> GetToc() const;

	DriverCaps::Type GetCaps() const override;

	Handle *Open(const char *path, Mode mode = ModeRead) override;
	void Close(Handle &h) override;

	bool Delete(const char *path) override;

	size_t Tell(Handle &h) override;
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef = SeekCurrent) override;
	size_t Size(Handle &h) override;

	bool IsEOF(Handle &h) override;

	size_t Read(Handle &h, void *out, size_t size) override;
	size_t Write(Handle &h, const void *in, size_t size) override;

	bool MkDir(const char *unused(path)) override { return false; }

private:
	mutable std::mutex fat_mutex;

	MemoryFat fat;
};

} // io
} // gs
