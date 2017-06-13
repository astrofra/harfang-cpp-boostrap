#pragma once

#include "agg_font_cache_manager.h"
#include "agg_font_freetype.h"

namespace gs {

typedef agg::font_engine_freetype_int16 agg_font_engine;
typedef agg::font_cache_manager<agg_font_engine> agg_cache_manager;

struct AggPimpl {
	AggPimpl() : manager(engine) {}
	agg_font_engine engine;
	agg_cache_manager manager;
};

} // gs
