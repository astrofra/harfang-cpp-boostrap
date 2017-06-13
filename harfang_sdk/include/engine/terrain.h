// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/component.h"
#include "foundation/vector2.h"
#include "foundation/vector3.h"
#include <memory>
#include <string>

namespace gs { class Picture;
namespace gpu { struct Texture; }
namespace render { struct IRenderable; }
namespace core {

struct TerrainData;

/// Terrain renderable
class Terrain : public std::enable_shared_from_this<Terrain>, public Component {
public:
	static const int terrain_max_recursion = 32;

	Terrain();

	decl_component_defaults(Terrain, "Terrain");

	comp_decl_member_get_sync_set_async_noimpl(Terrain, std::string, Heightmap, heightmap);
	comp_decl_member_get_sync_set_async_noimpl(Terrain, iVector2, HeightmapResolution, heightmap_resolution);
	comp_decl_member_get_sync_set_async_noimpl(Terrain, uint, HeightmapBpp, heightmap_bpp);

	comp_decl_member_get_sync_set_async_noimpl(Terrain, Vector3, Size, size); // in meters

	comp_decl_member_get_sync_set_async_noimpl(Terrain, std::string, SurfaceShader, surface_shader);

	comp_decl_member_get_sync_set_async_validated(Terrain, int, PatchSubdivisionThreshold, patch_subdv_threshold, PatchSubdivisionThresholdValidator); // maximum normalized size of a patch subdivision on screen
	comp_decl_member_get_sync_set_async_validated(Terrain, int, MaxRecursion, max_recursion, MaxRecursionValidator); // maximum patch recursion
	comp_decl_member_get_sync_set_async_validated(Terrain, float, MinPrecision, min_precision, MinPrecisionValidator); // minimum patch subdivision size in meters

	comp_decl_member_get_sync_set_async(Terrain, bool, Wireframe, wireframe);

	std::shared_ptr<render::IRenderable> GetIRenderable() const override { return renderable; }

	ComponentState GetState() const override;

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

private:
	std::shared_ptr<render::IRenderable> renderable;

	static int PatchSubdivisionThresholdValidator(Terrain *terrain, int value) { return value > 1 ? value : 1; }
	static int MaxRecursionValidator(Terrain *terrain, int value) { return types::Clamp(value, 0, terrain_max_recursion); }
	static float MinPrecisionValidator(Terrain *terrain, float value) { return value > 0.01f ? value : 0.01f; } // limit to 10cm
};

/// Load a terrain heightmap to a picture object.
bool LoadHeightmap(Picture &heightmap_pic, const char *path, uint width, uint height, uint bpp);
/// Normalize an heightmap picture.
bool NormalizeHeightmap(Picture &heightmap, uint invalid_value);
/// Save heightmap picture.
bool SaveHeightmap(const Picture &heightmap, const char *path);

} // core
} // gs
