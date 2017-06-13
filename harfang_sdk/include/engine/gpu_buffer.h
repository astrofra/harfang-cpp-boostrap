// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <memory>

#include "foundation/get_type_name.h"
#include "foundation/task.h"

namespace gs {
namespace gpu {

class Renderer;

struct Buffer {
	enum Usage { Static, Dynamic };
	enum Type { Index, Vertex };
};

typedef std::shared_ptr<Buffer> sBuffer;

void BufferDeleter(Buffer *buffer, std::weak_ptr<Renderer> renderer_weak, task_affinity worker);

} // gpu

DeclareTypeName(gpu::Buffer, "gs::gpu::Buffer")

} // gs
