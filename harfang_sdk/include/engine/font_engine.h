// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/rect.h"
#include <memory>
#include <string>
#include <vector>

namespace gs {

struct GlyphInfo {
	iRect rect;
	Vector2 advance;
};

struct AggPimpl;

class FontEngine {
public:
	static const int storage_size = 32;

	FontEngine();
	~FontEngine();

	bool SetFont(const char *path, bool autohint = false);
	void SetSize(float size);

	GlyphInfo GetGlyphInfo(std::u32string::value_type codepoint);
	fRect GetTextRect(const std::u32string::value_type *codepoints, uint count, float x, float y);
	fRect GetTextRect(const char *utf8, float x, float y);

	bool GetKerning(std::u32string::value_type first_codepoint, std::u32string::value_type second_codepoint, float &kerning_x, float &kerning_y);

	std::unique_ptr<AggPimpl> agg_pimpl;

private:
	struct Font {
		std::string path;
		std::vector<char> data;
	};

	std::vector<Font> fonts;

	float size = 12.f;
};

} // gs
