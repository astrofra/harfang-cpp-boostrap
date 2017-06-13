// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_handle.h"
#include "foundation/io_memory.h"
#include <map>
#include <memory>
#include <mutex>

namespace gs {
namespace io {

struct Zip_engine;

/// Zip-based I/O
class Zip : public Driver {
public:
	typedef std::map<std::string, int> RefcMap;

	Zip(std::shared_ptr<Handle> archive, const char *password = nullptr);
	~Zip();

	bool SetArchive(std::shared_ptr<Handle> archive, const char *password = nullptr);

	DriverCaps::Type GetCaps() const override;

	Handle *Open(const char *, Mode = ModeRead) override;
	void Close(Handle &) override;

	bool Delete(const char *) override;

	size_t Tell(Handle &) override;
	size_t Seek(Handle &, ptrdiff_t offset, SeekRef = SeekCurrent) override;
	size_t Size(Handle &h) override;

	bool IsEOF(Handle &h) override;

	size_t Read(Handle &, void *, size_t) override;
	size_t Write(Handle &, const void *, size_t) override;

	std::vector<DirEntry> Dir(const char *path, const char *wildcard, DirEntry::Type filter = DirEntry::All) override;
	bool MkDir(const char *) override { return false; }

private:
	std::mutex zip_mutex;

	std::unique_ptr<Zip_engine> zip_engine;
	std::shared_ptr<Handle> archive;

	void *zfile;
	std::string password;

	RefcMap refc_map;
	std::shared_ptr<Memory> memory_driver; // for nested compressed zip
};

} // io
} // gs
