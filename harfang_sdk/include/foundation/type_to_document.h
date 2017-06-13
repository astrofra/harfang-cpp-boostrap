// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"

namespace gs {

enum SerializeFlags {
	SerializeDefault = 0,
	SerializeIgnoreTypeSerializer = 0x1,
};

bool SerializeEx(IDocumentWriter &doc, const void *o, const Type *type, SerializationContext *ctx = nullptr, const char *name = nullptr, SerializeFlags flags = SerializeDefault);
bool Serialize(IDocumentWriter &doc, const void *o, const Type *type, SerializationContext *ctx = nullptr, const char *name = nullptr);

enum DeserializeFlags {
	DeserializeDefault = 0,
	DeserializeIgnoreTypeSerializer = 0x1,
};

bool DeserializeEx(IDocumentReader &doc, void *o, const Type *type, DeserializationContext *ctx = nullptr, const char *name = nullptr, DeserializeFlags flags = DeserializeDefault);
bool Deserialize(IDocumentReader &doc, void *o, const Type *type, DeserializationContext *ctx = nullptr, const char *name = nullptr);

// This types mostly exist to reduce the SWIG binding complexity by hiding low-level details.
struct SerializationState {
	SerializationState(IDocumentWriter *d = nullptr, const SerializationContext *c = nullptr) : doc(d), ctx(c) {}

	IDocumentWriter *doc;
	const SerializationContext *ctx;
};

struct DeserializationState {
	DeserializationState(const IDocumentReader *d = nullptr, DeserializationContext *c = nullptr) : doc(d), ctx(c) {}

	const IDocumentReader *doc;
	const DeserializationContext *ctx;
};

} // gs
