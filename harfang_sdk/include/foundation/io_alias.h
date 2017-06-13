// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_driver.h"
#include "foundation/map.h"
#include <map>
#include <string>

namespace gs {
namespace io {

class Handle;

/*!
	@short Alias proxy I/O.
	A simple proxy I/O to provide filename aliasing to another I/O system.
*/
class Alias : public Driver {
public:
	Alias(Driver *io) : iofs(io) {}

	Handle *Open(const char *path, Mode mode = ModeRead) override { return iofs->Open(ResolveAlias(path).c_str(), mode); }
	void Close(Handle &h) override { iofs->Close(h); }

	bool Delete(const char *path) override { return iofs->Delete(ResolveAlias(path).c_str()); }

	size_t Tell(Handle &h) override { return iofs->Tell(h); }
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef seek_ref = SeekCurrent) override { return iofs->Seek(h, offset, seek_ref); }

	size_t Read(Handle &h, void *p, size_t size) override { return iofs->Read(h, p, size); }
	size_t Write(Handle &h, const void *p, size_t size) override { return iofs->Write(h, p, size); }

	bool RegisterAlias(const char *alias, const char *source) {
		if (alias_map.find(alias) == alias_map.end())
			return false;
		alias_map[alias] = source;
		return true;
	}

private:
	std::shared_ptr<Driver> iofs;

	typedef std::map<std::string, std::string> AliasMap;

	AliasMap alias_map;

	std::string ResolveAlias(const char *path) const {
		auto alias = alias_map.find(path);
		if (alias == alias_map.end())
			return path;
		return (*alias).second;
	}
};

} // io
} // gs
