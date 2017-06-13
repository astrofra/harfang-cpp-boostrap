// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/shader.h"
#include "engine/types.h"

namespace gs {
namespace core {

enum IndexType : uint8_t {
	IndexUByte,
	IndexUShort,
	IndexUInt,

	IndexLast
};

extern size_t IndexTypeSize[IndexLast];

enum VertexType : uint8_t { // do not mistake for ShaderType
	VertexByte,
	VertexUByte,
	VertexShort,
	VertexUShort,
	VertexInt,
	VertexUInt,
	VertexFloat,
	VertexHalfFloat,

	VertexLast
};

extern size_t VertexTypeSize[VertexLast];

struct VertexLayout {
	typedef uint8_t Stride;

	static const int max_attribute = 8;

	struct Attribute { // 2 bytes
		Attribute() : semantic(core::VertexAttribute::LastSemantic), count(0), type(VertexByte), is_normalized(false) {}

		core::VertexAttribute::Semantic semantic : 8;
		uint8_t count : 4;
		VertexType type : 3;
		uint8_t is_normalized : 1;

		inline size_t ComputeSize() const {
			size_t size = count * VertexTypeSize[type];
			return (size & 1) ? size + 1 : size; // always align attributes
		}
	};

	inline bool operator==(const VertexLayout &layout) const { return memcmp(this, &layout, sizeof(VertexLayout)) == 0; }
	inline bool operator!=(const VertexLayout &layout) const { return !(*this == layout); }

	void Clear();
	bool AddAttribute(core::VertexAttribute::Semantic semantic, uint8_t count, VertexType type, bool is_normalized = false);
	void End();

	const Attribute *GetAttribute(core::VertexAttribute::Semantic semantic) const;

	Stride stride = 0;
	Attribute attr[max_attribute];
};

struct StdVertexLayout {
	StdVertexLayout();

	VertexLayout pos;
	VertexLayout pos_uv0;
	VertexLayout pos_uv0_color0;
};

extern StdVertexLayout std_vertex_layout;

} // core
} // gs
