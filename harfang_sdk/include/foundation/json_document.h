// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/document.h"
#include <memory>

namespace gs {

struct JSON_reader_pimpl;

class JSONDocumentReader : public IDocumentReader {
public:
	JSONDocumentReader();
	~JSONDocumentReader();

	std::string GetScopeName() const override;

	bool EnterFirstChild() override;
	bool EnterSibling() override;
	bool ExitScope() override;

	bool Read(const char *name, bool &) override;
	bool Read(const char *name, int32_t &) override;
	bool Read(const char *name, uint32_t &) override;
	bool Read(const char *name, float &) override;
	bool Read(const char *name, std::string &) override;

	bool Load(const char *url) override;
	bool FromString(const char *json);

private:
	std::unique_ptr<JSON_reader_pimpl> reader;
};

struct JSON_writer_pimpl;

class JSONDocumentWriter : public IDocumentWriter {
public:
	JSONDocumentWriter();
	~JSONDocumentWriter();

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
	std::unique_ptr<JSON_writer_pimpl> writer;
};

} // gs
