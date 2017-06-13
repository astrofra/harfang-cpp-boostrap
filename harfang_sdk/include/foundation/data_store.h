// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_handle.h"
#include "foundation/string.h"
#include "foundation/unit.h"
#include <mutex>

namespace gs {
namespace io {

/// Data store
class DataStore {
public:
	struct Entry {
		std::string id;
		std::string user;
		size_t size = 0;
	};

	DataStore(sDriver storage, size_t storage_limit = units::MB(32)) : driver(storage), limit(storage_limit), id_seed(0) { entries.reserve(64); }

	const sDriver &GetDriver() const { return driver; }

	const std::vector<Entry> &GetEntries() const { return entries; }

	/// Reserve space on the store, an empty id is returned if the store is full.
	virtual std::string Reserve(size_t size);
	/// Free a store alias.
	virtual bool Free(const std::string &id);

	/// Store data on a reserved id.
	bool Store(const std::string &id, const void *data, size_t size, const char *user_data = nullptr);

	/// Get entry size.
	size_t GetEntrySize(const std::string &id);

	/// Get the current store size.
	size_t GetStoreSize() const;
	/// Get the store free space size.
	size_t GetFreeStore() const;

	/// Restore store content from the storage fs.
	bool Load(const char *path = "store.db");
	/// Save store content to the storage fs.
	bool Save(const char *path = "store.db");

private:
	std::mutex access;

	sDriver driver;
	size_t limit;

	uint32_t id_seed;
	std::string GetNewId();

	std::vector<Entry> entries;
	std::vector<Entry>::iterator GetEntry(const std::string &id);
};

} // io
} // gs
