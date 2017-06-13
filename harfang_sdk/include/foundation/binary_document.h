// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/document.h"
#include "foundation/io_handle.h"

namespace gs {

class BinaryBlob;

enum BinaryChunkType { Type_Scope, Type_Bool, Type_Int, Type_Unsigned, Type_Float, Type_String, Type_Binary };

class BinaryDocumentWriter : public IDocumentWriter
{
public:
	struct Scope {
		Scope() : o_scope(0), o_scope_size(0) {}
		size_t o_scope;
		size_t o_scope_size;
	};

	BinaryDocumentWriter() : cursor(0) {}

	bool EnterScope(const char *name) override;
	bool ExitScope() const override;

	bool Write(const char *name, bool) override;
	bool Write(const char *name, int32_t) override;
	bool Write(const char *name, uint32_t) override;
	bool Write(const char *name, float) override;
	bool Write(const char *name, const std::string &) override;

	/// Prevent implicit cast from const char * to bool.
	bool Write(const char *name, const char *v) { return Write(name, std::string(v)); }

	bool HasBinarySupport() const override { return true; }
	bool Write(const char *name, const BinaryBlob &) override;

	bool Save(BinaryBlob &out);
	bool Save(const char *url) override;

private:
	mutable std::vector<Scope> stack;

	mutable std::vector<char> data;
	size_t cursor;

	template <typename T> bool TWrite(const T &v)
	{
		while (cursor + sizeof(T) > data.size())
			data.resize(data.size() + 32768);

		*reinterpret_cast<T *>(&data[cursor]) = v;
		cursor += sizeof(T);

		return true;
	}

	bool BWrite(const void *p, size_t size)
	{
		if (cursor + size > data.size())
			data.resize(data.size() + size + 32768);

		memcpy(&data[cursor], p, size);
		cursor += size;
		return true;
	}

	inline char *OffsetToAddress(size_t o) const { return &data[o]; }

	std::vector<std::string> dictionary;

	bool OutputString(const char *name);
	bool SaveDictionary(BinaryBlob &) const;
};

class BinaryDocumentReader : public IDocumentReader
{
public:
	BinaryDocumentReader() : cursor(0) {}

	std::string GetScopeName() const override;

	bool EnterFirstChild() override;
	bool EnterSibling() override;
	bool ExitScope() override;

	bool Read(const char *name, bool &) override;
	bool Read(const char *name, int32_t &) override;
	bool Read(const char *name, uint32_t &) override;
	bool Read(const char *name, float &) override;
	bool Read(const char *name, std::string &) override;

	bool HasBinarySupport() const override { return true; }
	bool Read(const char *name, BinaryBlob &) override;

	bool Load(const BinaryBlob &blob);
	bool Load(const char *url) override;

private:
	std::vector<char> data;
	size_t cursor;

	bool LoadInternal();

	struct Chunk;
	typedef std::vector<std::unique_ptr<Chunk>> ChunkList;

	struct Chunk {
		Chunk() : name_index(0), data(nullptr), offset(0), size(0), type(Type_Scope) {}

		uint16_t name_index;
		const char *data;
		size_t offset, size;
		BinaryChunkType type;

		ChunkList chunks;
		ChunkList::iterator current_scope_index;
	};

	char *OffsetToAddress(size_t o) { return &data[o]; }

	std::vector<const char *> dictionary;
	const char *GetString(uint16_t index) const;
	bool LoadDictionary(size_t, size_t);

	bool ParseChunk(Chunk *);
	bool ParseChunkTree(size_t, size_t, ChunkList &);

	ChunkList &GetCurrentChunks();
	ChunkList::iterator &GetCurrentScopeIndex();

	Chunk *CurrentChunk() const;
	Chunk *CurrentChunkChild(std::string name);

	mutable ChunkList::iterator current_scope_index;
	bool EnterChunk(Chunk *s);

	ChunkList root_chunks;
	mutable std::vector<Chunk *> stack;
};

} // gs
