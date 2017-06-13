// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector2.h"
#include "foundation/vector3.h"
#include "foundation/color.h"
#include <map>
#include <memory>
#include <vector>

namespace gs {
namespace gpu { struct Texture; }
namespace render {

class RenderSystem;

class RasterFontBatch {
public:
	void AddGlyph(const Vector3 vtxs[4], const Vector2 uvs[4], const Color rgbs[4], std::shared_ptr<gpu::Texture> page);
	void Draw(RenderSystem &render_system);

private:
	struct Batch {
		static const int reserve_glyph = 64;

		Batch() {
			vtxs.reserve(4 * reserve_glyph);
			uvs.reserve(4 * reserve_glyph);
			rgbs.reserve(4 * reserve_glyph);
		}

		void Clear() {
			vtxs.clear();
			uvs.clear();
			rgbs.clear();
		}

		std::vector<Vector3> vtxs;
		std::vector<Vector2> uvs;
		std::vector<Color> rgbs;
	};

	std::map<std::shared_ptr<gpu::Texture>, Batch> batches;
	std::vector<uint16_t> idxs;

	uint16_t *GetIndices(uint glyph_count);
};

} // core
} // gs
