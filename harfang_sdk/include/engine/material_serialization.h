// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"

namespace gs {

struct IDocumentReader;
struct IDocumentWriter;

struct MaterialTypeSerializer : TypeSerializer {
	virtual bool Deserialize(IDocumentReader &doc, void *o, const Type *type, DeserializationContext *ctx = nullptr, const char *name = nullptr) override;
	virtual bool Serialize(IDocumentWriter &doc, const void *o, const Type *type, SerializationContext *ctx = nullptr, const char *name = nullptr) override;
};

} // gs
