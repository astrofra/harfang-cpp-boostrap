// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/types.h"
#include <string>
#include <cstdint>

namespace gs {

class BinaryBlob;

struct IDocumentReader {
	virtual ~IDocumentReader() {}

	virtual std::string GetScopeName() const = 0;

	/// Get the number of scope children with a specific name.
	uint GetChildCount();
	uint GetChildCount(const char *name);

	/*!
		@short Enter a child scope with a specific name.
		@note This helper function simply wraps EnterFirstChild and EnterSibling
		calls.
	*/
	bool EnterScope(const char *name);
	bool EnterScopeMultiple(const char *name);
	bool ExitScopeMultiple(uint count);

	/*!
		@short Enter the first child scope to the current scope.
		If no such scope exists this function returns false.
	*/
	virtual bool EnterFirstChild() = 0;
	/*!
		@short Enter the sibling scope to the current scope.
		If no such scope exists the parent scope is entered and this function
		returns false.
	*/
	virtual bool EnterSibling() = 0;
	/// Exit current scope.
	virtual bool ExitScope() = 0;

	virtual bool Read(const char *name, bool &) = 0;
	virtual bool Read(const char *name, int32_t &) = 0;
	virtual bool Read(const char *name, uint32_t &) = 0;
	virtual bool Read(const char *name, float &) = 0;
	virtual bool Read(const char *name, std::string &) = 0;

	bool Read(const char *name, char &v); // stored as int32_t
	bool Read(const char *name, uint8_t &v); // stored as uint32_t
	bool Read(const char *name, short &v); // stored as int32_t
	bool Read(const char *name, uint16_t &v); // stored as uint32_t

	virtual bool HasBinarySupport() const { return false; }
	virtual bool Read(const char *, BinaryBlob &) { return false; }

	virtual bool Load(const char *path) = 0;
};

struct IDocumentWriter {
	virtual ~IDocumentWriter() {}

	bool EnterScopeMultiple(const char *name);
	bool ExitScopeMultiple(uint count);

	virtual bool EnterScope(const char *name) = 0;
	virtual bool ExitScope() const = 0;

	virtual bool Write(const char *name, bool) = 0;
	virtual bool Write(const char *name, int32_t) = 0;
	virtual bool Write(const char *name, uint32_t) = 0;
	virtual bool Write(const char *name, float) = 0;
	virtual bool Write(const char *name, const std::string &) = 0;

	bool Write(const char *name, char); // stored as int32_t
	bool Write(const char *name, uint8_t); // stored as uint32_t
	bool Write(const char *name, short); // stored as int32_t
	bool Write(const char *name, uint16_t); // stored as uint32_t

	/// Prevent implicit cast from const char * to bool.
	bool Write(const char *name, const char *v) { return Write(name, std::string(v)); }

	virtual bool HasBinarySupport() const { return false; }
	virtual bool Write(const char *, const BinaryBlob &) { return false; }

	virtual bool Save(const char *path) = 0;
};

class WriteScopeGuard
{
public:
	WriteScopeGuard(const WriteScopeGuard &) = delete;
	WriteScopeGuard(IDocumentWriter &d) : doc(d) { has_entered = false; }
	WriteScopeGuard(IDocumentWriter &d, const char *name) : doc(d) { has_entered = doc.EnterScope(name); }
	~WriteScopeGuard() { Exit(); }

	/// Return true if this guard will exit scope when destroyed.
	inline bool HasEnteredScope() const { return has_entered; }
	/// Explicitly enter a scope.
	bool Enter(const char *name) { return has_entered ? false : (has_entered = doc.EnterScope(name)); }

	/// Exit the guarded scope, returns false if no scope was exited.
	bool Exit();

private:
	IDocumentWriter &doc;
	bool has_entered;
};

enum DocumentFormat { DocumentFormatUnknown, DocumentFormatXML, DocumentFormatJSON, DocumentFormatBinary };

DocumentFormat GetDocumentReadFormat(const char *path);
DocumentFormat GetDocumentWriteFormat(const char *path);

DocumentFormat GetDocumentFormatFromString(const std::string &document);

} // gs
