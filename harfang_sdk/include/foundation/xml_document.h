// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/document.h"
#include <memory>

namespace gs {

struct XML_reader_pimpl;

class XMLDocumentReader : public IDocumentReader {
public:
	XMLDocumentReader();
	~XMLDocumentReader();

	std::string GetScopeName() const override;

	bool EnterFirstChild() override;
	bool EnterSibling() override;
	bool ExitScope() override;

	bool Read(const char *name, bool &) override;
	bool Read(const char *name, int32_t &) override;
	bool Read(const char *name, uint32_t &) override;
	bool Read(const char *name, float &) override;
	bool Read(const char *name, std::string &) override;

	bool Load(const char *path) override;
	bool FromString(const char *xml);

private:
	std::unique_ptr<XML_reader_pimpl> reader;
};

struct XML_writer_pimpl;

class XMLDocumentWriter : public IDocumentWriter {
public:
	XMLDocumentWriter();
	~XMLDocumentWriter();

	bool EnterScope(const char *name) override;
	bool ExitScope() const override;

	bool Write(const char *name, bool) override;
	bool Write(const char *name, int32_t) override;
	bool Write(const char *name, uint32_t) override;
	bool Write(const char *name, float) override;
	bool Write(const char *name, const std::string &) override;

	/// Prevent implicit cast from const char * to bool.
	bool Write(const char *name, const char *v) { return Write(name, std::string(v)); }

	bool Save(const char *path) override;
	std::string ToString() const;

private:
	std::unique_ptr<XML_writer_pimpl> writer;
};

} // gs
