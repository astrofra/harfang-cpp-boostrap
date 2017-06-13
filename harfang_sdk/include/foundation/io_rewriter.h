// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/io_driver.h"
#include "foundation/string.h"

namespace gs {
namespace io {

class Handle;

/*!
	@short Rewriter proxy I/O.
	A simple proxy I/O to rewrite filenames before forwarding them to another I/O system.

	The rewriting rule can make use of the following symbols to rewrite a path.
		* %path%: The path to be rewritten.
*/
class Rewriter : public Driver
{
public:
	Rewriter(sDriver io, const char *rule) : iofs(io), rewriter_rule(rule) {}

	DriverCaps::Type GetCaps() const override { return iofs->GetCaps(); }

	Handle *Open(const char *path, Mode mode = ModeRead) override { return iofs->Open(RewritePath(path).c_str(), mode); }
	void Close(Handle &h) override { iofs->Close(h); }

	bool Delete(const char *path) override { return iofs->Delete(RewritePath(path).c_str()); }

	size_t Tell(Handle &h) override { return iofs->Tell(h); }
	size_t Seek(Handle &h, ptrdiff_t offset, SeekRef seek_ref = SeekCurrent) override { return iofs->Seek(h, offset, seek_ref); }
	size_t Size(Handle &h) override { return iofs->Size(h); }

	bool IsEOF(Handle &h) override { return iofs->IsEOF(h); }

	size_t Read(Handle &h, void *p, size_t size) override { return iofs->Read(h, p, size); }
	size_t Write(Handle &h, const void *p, size_t size) override { return iofs->Write(h, p, size); }

	bool MkDir(const char *path) override { return iofs->MkDir(RewritePath(path).c_str()); }

private:
	sDriver iofs;
	std::string rewriter_rule;

	std::string RewritePath(const char *path) const
	{
		std::string output(rewriter_rule);
		replace_all(output, "%path%", path);
		return output;
	}
};

} // io
} // gs
