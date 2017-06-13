// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/cext.h"
#include "foundation/base_handle.h"
#include "foundation/io_mode.h"
#include "foundation/vector.h"
#include <memory>
#include <string>

namespace gs {
namespace io {

class Handle;

struct DirEntry {
	enum Type { Invalid = 0, File, Directory, All };

	Type type = Invalid;
	std::string name;
};

/// I/O driver
class Driver : public std::enable_shared_from_this<Driver> {
public:
	virtual ~Driver() {}

	virtual std::string FileHash(const char *path);

	virtual std::string MapToAbsolute(std::string path) const { return path; }
	virtual std::string MapToRelative(std::string path) const { return path; }

	virtual DriverCaps::Type GetCaps() const = 0;

	virtual Handle *Open(const char *path, Mode mode = ModeRead) = 0;
	virtual void Close(Handle &h) = 0;

	virtual bool Delete(const char *path) = 0;

	virtual size_t Tell(Handle &h) = 0;
	virtual size_t Seek(Handle &h, ptrdiff_t offset, SeekRef seek = SeekCurrent) = 0;
	virtual size_t Size(Handle &h) = 0;

	virtual bool IsEOF(Handle &h) = 0;

	virtual size_t Read(Handle &h, void *buffer_out, size_t size) = 0;
	virtual size_t Write(Handle &h, const void *buffer_in, size_t size) = 0;

	virtual std::vector<DirEntry> Dir(const char *path, const char *wildcard = "*.*", DirEntry::Type filter = DirEntry::All);
	virtual bool MkDir(const char *path) = 0;
	virtual bool IsDir(const char *unused(path)) { return false; }
};

typedef std::shared_ptr<Driver> sDriver;

/// Return the content of a file as a string.
std::string FileToString(Driver &driver, const char *path);
/// Test if a file exists on the driver.
bool FileExists(Driver & driver, const char *path);

/// Return the content of a file as a byte buffer.
bool FileLoad(Driver &driver, const char *path, std::vector<char> &buffer);
/// Save a byte buffer to a file.
bool FileSave(Driver &driver, const char *path, const std::vector<char> &buffer);

/// Test if a file or directory exists on a driver.
bool Exists(Driver &driver, const char *path);

} // io
} // gs
