// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector.h"
#include <cstdint>
#include <cstring>

namespace gs {

class BinaryBlob {
public:
	explicit BinaryBlob(size_t s) : data_size(0), cursor(0) { Grow(s); }

	BinaryBlob() : data_size(0), cursor(0) {}
	BinaryBlob(const void *p, size_t s) : data_size(0), cursor(0) { Write(p, s); }
	BinaryBlob(const BinaryBlob &blob) : data_size(0), cursor(0) { *this = blob; }
	BinaryBlob(BinaryBlob &&blob) : storage(std::move(blob.storage)), data_size(blob.data_size), cursor(blob.cursor) {}

	BinaryBlob &operator=(const BinaryBlob &blob) {
		Free();
		storage = blob.storage;
		data_size = blob.data_size;
		cursor = blob.cursor;
		return *this;
	}

	BinaryBlob &operator=(BinaryBlob &&blob) {
		Free();
		storage = std::move(blob.storage);
		data_size = blob.data_size;
		cursor = blob.cursor;
		return *this;
	}

	BinaryBlob &operator=(const std::vector<char> &data_) {
		Free();
		Write(data_.data(), memory_usage(data_));
		return *this;
	}

	std::vector<char> GetByteArray() const {
		std::vector<char> data_(GetDataSize());
		memcpy(data_.data(), storage.data(), data_size);
		return data_;
	}

	/// Return a pointer to the blob storage.
	inline char *GetData() { return storage.data(); }
	inline const char *GetData() const { return storage.data(); }
	/// Return the blob data size.
	inline size_t GetDataSize() const { return data_size; }

	/// Return the cursor position.
	inline size_t GetCursor() const { return cursor; }
	/// Set the cursor position.
	inline void SetCursor(size_t position) {
		auto data_size_ = storage.size();
		if (position > data_size_)
			Grow(position - data_size_);
		cursor = position;
	}

	/// Return a pointer to the cursor.
	inline char *GetCursorPtr() { return storage.data() + cursor; }
	inline const char *GetCursorPtr() const { return storage.data() + cursor; }
	/// Return available data size from the cursor position.
	inline size_t GetDataSizeAtCursor() const { return data_size - cursor; }

	/// Reset the blob data.
	inline void Reset() { data_size = cursor = 0; }

	/// Commit a write to the blob storage.
	inline void Commit(size_t size) {
		Grow(size);

		cursor += size;
		if (cursor > data_size)
			data_size = cursor;
	}

	/// Grow the blob storage at cursor position.
	inline void Grow(size_t s) {
		auto required_size = ((cursor + s) / 8192 + 1) * 8192; // grow in 8KB increments
		if (required_size > storage.size())
			storage.resize(required_size);
	}

	void Skip(size_t s) {
		Grow(s);
		cursor += s;
		data_size = data_size > cursor ? data_size : cursor;
	}

	void Write(const void *v, size_t s) {
		Grow(s);
		memcpy(&storage[cursor], v, s);
		cursor += s;
		data_size = data_size > cursor ? data_size : cursor;
	}

	template <typename T> inline void Write(const T &v) { Write(&v, sizeof(T)); }

	template <typename T> inline void WriteAt(const T &v, size_t position) {
		SetCursor(position);
		Write(v);
	}

	bool Read(void *v, size_t s) const {
		if (cursor + s > data_size)
			return false;

		memcpy(v, &storage[cursor], s);
		cursor += s;
		return true;
	}

	template <typename T> inline bool Read(T &v) const { return Read(&v, sizeof(T)); }

	template <typename T> inline bool ReadAt(T &v, size_t position) const {
		cursor = position;
		return Read(&v, sizeof(T));
	}

	void Free() {
		storage.clear();
		data_size = 0;
		cursor = 0;
	}

private:
	std::vector<char> storage;
	size_t data_size;

	mutable size_t cursor;
};

std::vector<char> BinaryBlobToByteArray(const BinaryBlob &blob);
BinaryBlob BinaryBlobFromByteArray(const std::vector<char> &data);

void BinaryBlobBlur3d(BinaryBlob &blob, uint32_t width, uint32_t height, uint32_t depth);

} // gs
