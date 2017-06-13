// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>

#include "foundation/data_store.h"
#include "foundation/io_driver.h"
#include "foundation/types.h"
#include "foundation/time.h"

namespace gs {
namespace io {

/*!
	@short Cached I/O filesystem wrapper
	Implements a transparent file cache on top of another filesystem.
*/
class Cache : public Driver {
public:
	struct Entry {
		std::string path, id;
		std::string hash;

		uint refc = 0;
		size_t size = 0;

		time_t last_use;
	};

	typedef std::vector<Entry> EntryList;

	Cache(sDriver driver, sDriver store, size_t cache_size = units::MB(32));

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

	bool MkDir(const char *) override;

	/// Test if a given path is in cache.
	bool IsInCache(const char *path) { return GetCacheEntry(path) != entries.end(); }

	/// Reload cache state from its store.
	bool SynchronizeWithStore(const char *store_path = "store.db");

private:
	sDriver driver;
	DataStore store;

	std::mutex cache_mutex;

	size_t cache_size;
	EntryList entries;

	std::string ReserveOnStore(size_t size);

	EntryList::iterator GetCacheEntry(const char *path);
	EntryList::iterator CreateCacheEntry(const char *path);
	bool UpdateCacheEntry(Entry &entry, std::vector<char> *preloaded_data = nullptr);
	bool DeleteCacheEntry(EntryList::iterator i);
};

} // io
} // gs
