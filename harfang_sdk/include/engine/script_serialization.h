// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"

namespace gs {
namespace core {

struct ScriptParamListSerializer : TypeSerializer {
	bool Deserialize(IDocumentReader &doc, void *o, const Type *type, DeserializationContext *ctx = nullptr, const char *name = nullptr) override;
	bool Serialize(IDocumentWriter &doc, const void *o, const Type *type, SerializationContext *ctx = nullptr, const char *name = nullptr) override;
};

} // core
} // gs
