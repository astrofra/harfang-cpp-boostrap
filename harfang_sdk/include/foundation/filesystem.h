// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/global_object.h"
#include "foundation/io_driver.h"
#include "foundation/string.h"

namespace gs {
namespace io {

class MountPoint {
public:
	MountPoint(const char *prefix_, sDriver driver_) : prefix(prefix_), driver(std::move(driver_)) {}

	inline const std::string &GetPrefix() const { return prefix; }
	inline const sDriver &GetDriver() const { return driver; }

	inline std::string StripPrefix(const char *path) const { return strip_prefix(std::string(path), prefix); }

private:
	std::string prefix;
	sDriver driver;
};

/// I/O system
class Filesystem {
public:
	Filesystem();
	~Filesystem();

	bool Mount(sDriver driver);
	bool Mount(sDriver driver, const char *prefix);
	bool IsPrefixMounted(const char *prefix) const { return GetMountPoint(prefix) != nullptr; }

	void Unmount(const char *path);
	void Unmount(const sDriver &driver);
	void UnmountAll();

	std::string MapToAbsolute(const char *path) const;
	std::string MapToRelative(const char *path) const;
	std::string StripPrefix(const char *path) const;

	Handle *Open(const char *path, Mode mode = ModeRead) const;
	void Close(Handle &h) const;

	bool MkDir(const char *path) const;

	bool Exists(const char *path) const;
	bool Delete(const char *path) const;

	size_t FileSize(const char *path) const;
	bool FileLoad(const char *path, std::vector<char> &data_out, bool verbose = true) const;
	bool FileSave(const char *path, const std::vector<char> &data_in) const;
	bool FileSave(const char *path, const void *data_in, size_t size) const;
	bool FileCopy(const char *src, const char *dst) const;
	bool FileMove(const char *src, const char *dst) const;

	std::string FileToString(const char *path) const;
	bool StringToFile(const char *path, const std::string &text) const;

private:
	std::vector<MountPoint> mount_points;
	std::vector<sDriver> root_drivers;

	const MountPoint *GetMountPoint(const char *path) const;
};

} // io

extern global_object<io::Filesystem> g_fs;

} // gs
