// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"

namespace gs {

struct IDocumentReader;
struct IDocumentWriter;

namespace core {

struct GeometryTypeSerializer : TypeSerializer {
	bool Deserialize(IDocumentReader &doc, void *o, const Type *type, DeserializationContext *ctx = nullptr, const char *name = nullptr) override;
	bool Serialize(IDocumentWriter &doc, const void *o, const Type *type, SerializationContext *ctx = nullptr, const char *name = nullptr) override;
};

class Geometry;

/// Load a core geometry from path.
bool LoadGeometry(Geometry &geometry, const char *url);

} // core
} // gs
