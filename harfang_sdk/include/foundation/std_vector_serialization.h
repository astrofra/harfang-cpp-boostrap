// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>

#include "foundation/binary_blob.h"

namespace gs {

struct IDocumentReader;
struct IDocumentWriter;

template <typename T> bool DeserializeStdVector(IDocumentReader &doc, std::vector<T> &c, const char *element_name, DeserializationContext *ctx = nullptr) {
	static auto type = g_type_registry.get().GetType<T>();
	if (!type)
		return false;

	auto count = doc.GetChildCount(element_name);
	c.resize(count);

	count = 0;
	std::string name(element_name);
	if (doc.EnterFirstChild()) {
		do {
			if (element_name && doc.GetScopeName() != name) // check element name
				continue;
			if (!Deserialize(doc, &c[count++], type, ctx, "value"))
				return false;
		} while (doc.EnterSibling());
	}
	return true;
}

template <typename T> bool SerializeStdVector(IDocumentWriter &doc, const std::vector<T> &c, const char *name, const char *element_name, SerializationContext *ctx = nullptr) {
	static auto type = g_type_registry.get().GetType<T>();
	if (!type)
		return false;

	if (!c.size())
		return true;

	WriteScopeGuard hierarchy_guard(doc, name);
	for (uint n = 0; n < c.size(); ++n) {
		WriteScopeGuard guard(doc, element_name);
		if (!Serialize(doc, &c[n], type, ctx, "value"))
			return false;
	}
	return true;
}

template <typename T> bool DeserializeElementFromBinary(T &v, const BinaryBlob &input) { return input.Read(v); }

template <typename T> bool DeserializeStdVectorFromBinary(IDocumentReader &doc, std::vector<T> &c, bool (*deserialize_element)(T &, const BinaryBlob &) = &DeserializeElementFromBinary<T>) {
	uint32_t size;
	if (!doc.Read("Count", size))
		return false;

	c.resize(size);

	BinaryBlob blob;
	if (!doc.Read("Data", blob))
		return false;

	for (uint n = 0; n < c.size(); ++n)
		if (!deserialize_element(c[n], blob))
			return false;
	return true;
}

template <typename T> bool SerializeElementAsBinary(const T &v, BinaryBlob &blob) {
	blob.Write(v);
	return true;
}

template <typename T> bool SerializeStdVectorAsBinary(IDocumentWriter &doc, const std::vector<T> &c, const char *name, bool (*serialize_element)(const T &, BinaryBlob &) = &SerializeElementAsBinary<T>) {
	if (!c.size())
		return true;

	WriteScopeGuard root_scope(doc, name);
	doc.Write("Count", uint32_t(c.size())); // element count

	BinaryBlob blob; // vertex data as binary blob
	for (uint n = 0; n < c.size(); ++n)
		if (!serialize_element(c[n], blob))
			return false;
	return doc.Write("Data", blob);
}

} // gs
