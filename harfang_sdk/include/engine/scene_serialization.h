// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/reflection.h"
#include <memory>
#include <vector>

namespace gs {
namespace core { class Node; }

void RegisterSceneSerialization(TypeRegistry &registry);

/// Serialize a selection of nodes.
bool SerializeNodeSelection(IDocumentWriter &doc, const std::vector<std::shared_ptr<core::Node>> &nodes, SerializationContext *ctx);

} // gs
