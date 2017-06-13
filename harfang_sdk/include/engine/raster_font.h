// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/picture.h"
#include "engine/texture.h"
#include "foundation/color.h"
#include "foundation/rect_packer.h"
#include "foundation/utf8.h"
#include <map>

namespace gs {
namespace render {

class RenderSystem;

/*!
	@short Implement a raster font rasterizer and renderer.
	@note Must only be called from the render system thread.
*/
struct RasterFont {
	struct Page {
		gpu::sTexture texture;
		RectPacker<int> packer;
	};

	RasterFont(const char *font_path, float font_size, uint page_resolution = 512, uint glyph_margin = 2, bool autohint = false);

	/*!
		@short Prepare the glyph pages required to render a given text.
		This function can be used to prepare glyph pages before actual text
		drawing. Calling it before Draw() is optional.
	*/
	bool Prepare(RenderSystem &render_system, const char *utf8);
	/// Write an UTF8 string.
	bool Write(RenderSystem &render_system, const char *utf8, const Matrix4 &mat, Color color = Color::White, float scale = 1.f, bool snap_glyph_to_grid = true, bool orient_toward_camera = true);

	/// Return an UTF8 string bounding rectangle.
	fRect GetTextRect(RenderSystem &render_system, const char *utf8);

	bool Load(const RenderSystem &render_system, const char *base_path);
	bool Save(const RenderSystem &render_system, const char *base_path) const;

	const std::vector<Page> &GetPages() const { return pages; }

	float GetSize() const { return size; }

private:
	std::string path;
	float size;
	bool hinting;

	uint margin, resolution;

	Picture scratchpad; // page creation scratchpad texture

	std::vector<Page> pages;

	struct Glyph {
		int page = -1;
		GlyphInfo info;
		fRect uv;
	};

	std::map<utf32_cp, Glyph> glyphs;

	void PrepareGlyphs(RenderSystem &render_system, const utf32_cp *cps, uint count);

	// kerning cache
	struct GlyphPair {
		GlyphPair(utf32_cp a_, utf32_cp b_) : a(a_), b(b_) {}
		bool operator<(const GlyphPair &p) const { return a < p.a && b < p.b; }

		utf32_cp a, b;
	};

	std::map<GlyphPair, float> kerning_cache;

	float GetKerning(FontEngine &, utf32_cp p, utf32_cp c);
};

typedef std::shared_ptr<RasterFont> sRasterFont;

} // render
} // gs
