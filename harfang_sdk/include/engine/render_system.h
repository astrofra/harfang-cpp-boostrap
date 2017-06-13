// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/font_engine.h"
#include "engine/node.h"
#include "engine/raster_font_batch.h"
#include "engine/render_geometry.h"
#include "engine/render_primitive.h"
#include "engine/render_stats.h"
#include "engine/renderable.h"
#include "engine/renderer.h"
#include "engine/resource_cache.h"
#include "engine/state_cache.h"
#include "foundation/clock.h"
#include "foundation/frustum.h"

namespace gs {
namespace core { class LightSystem; }
namespace render {

struct RasterFont;

enum Eye { EyeMono, EyeStereoLeft, EyeStereoRight };

struct ViewState {
	fRect viewport, clipping;
	Matrix4 view;
	Matrix44 projection;
	FrustumPlanes frustum_planes;
	Eye eye;
};

/// Render system
class RenderSystem : public std::enable_shared_from_this<RenderSystem> {
public:
	enum RenderTechnique { TechniqueForward, TechniqueDeferred };

	struct Config {
		Config() : shadow_size(1024), fx_downscale(2), max_anisotropy(1), msaa_sample(1), enable_shadow(true) {}

		uint16_t shadow_size;

		uint fx_downscale : 4; // max 16
		uint max_anisotropy : 4; // max 16
		uint msaa_sample : 4; //max 16

		bool enable_shadow : 1;
	};

	struct ShadowMapData {
		gpu::sRenderTarget rt;
		gpu::sTexture map;

		float pcf_radius = 1.75f;
	};

	struct DirectVBO {
		gpu::sBuffer helper_idx, helper_vtx;
		gpu::sBuffer direct_idx, direct_vtx;

		gpu::sBuffer box_idx; // for deferred light volume drawing
	};

	struct Fog {
		float znear = 0, zfar = 0;
		Color color = Color::Black;
	};

	struct Environment {
		Color clear_color = Color::Black;
		Color ambient_color = Color::Black;
	};

	RenderSystem();
	~RenderSystem();

	RenderSystem(const RenderSystem &) = delete;

	const gpu::sRenderer &GetRenderer() const { return renderer; }

	bool Initialize(gpu::sRenderer renderer, bool support_3d = true);
	bool IsInitialized() const { return is_initialized; }
	void Free();

	void CreateShadowMaps();
	void FreeShadowMaps();

protected:
	iVector2 internal_resolution;

	sGeometry HasOrMakeGeometry(const char *name, bool use_cache, bool &was_in_cache);
	sMaterial HasOrMakeMaterial(const char *name, bool use_cache, bool &was_in_cache);

public:
	/// Return the system internal resolution.
	iVector2 GetInternalResolution() const { return internal_resolution; }
	/// Set the system internal resolution.
	void SetInternalResolution(const iVector2 &resolution);

	/// Get the viewport to internal resolution ratio.
	Vector2 GetViewportToInternalResolutionRatio() const;

	const Statistics &GetStatistics() const { return stats; }

	const Config &GetConfiguration() const { return config; }
	void SetAA(uint sample_count);

	const DirectVBO &GetDirectVBO() const { return direct_vbo; }
	const ShadowMapData &GetShadowMapData() const { return shadow_map_data; }

	uint PurgeCache();
	void RefreshCacheEntry(const char *name);

	sMaterial HasMaterial(const char *name) const { return materials.Has(name); }
	sMaterial LoadMaterial(const char *name, bool use_cache = true);
	sMaterial LoadMaterial(const char *name, const char *source, DocumentFormat format = DocumentFormatUnknown, bool use_cache = true);
	sMaterial CreateMaterial(const core::sMaterial &core_mat, bool use_cache = true);

	sGeometry HasGeometry(const char *name) const { return geometries.Has(name); }
	sGeometry LoadGeometry(const char *name, bool use_cache = true);
	sGeometry LoadGeometry(const char *name, const char *source, DocumentFormat format = DocumentFormatUnknown, bool use_cache = true);
	sGeometry CreateGeometry(const core::sGeometry &core_geo, bool use_cache = true);

	sSurfaceShader HasSurfaceShader(const char *name) const { return surface_shaders.Has(name); }
	sSurfaceShader LoadSurfaceShader(const char *name, const char *source, bool use_cache = true);
	sSurfaceShader LoadSurfaceShader(const char *path, bool use_cache = true);

	const TCache<Geometry> &GetGeometryCache() const { return geometries; }
	const TCache<Material> &GetMaterialCache() const { return materials; }
	const TCache<SurfaceShader> &GetSurfaceShaderCache() const { return surface_shaders; }

	RenderTechnique GetRenderTechnique() const { return render_technique; }
	void SetRenderTechnique(RenderTechnique technique);
	void FreeRenderTechnique();

	float GetFrameClock() const { return frame_clock; }

	void OnContextChanged();

	void SetView(const Matrix4 &view, const Matrix44 &projection, Eye eye = EyeMono);
	Eye GetEye() const { return eye; }

	ViewState GetViewState() const;
	void SetViewState(const ViewState &state);

	const FrustumPlanes &GetViewFrustum() const { return frustum; }

	uint UpdateLightVolumeBuffers(const core::Node &light, gpu::Buffer &idx, gpu::Buffer &vtx);

	FontEngine font_engine;
	RasterFontBatch font_batch;

	void DrawRasterFontBatch() { font_batch.Draw(*this); }

	StateCache state_cache;

	gpu::sBuffer instance_data_buffer;

	Fog fog;
	Environment environment;

	Matrix4 m_previous_iview, m_previous_world; // FIXME synchronize/set somewhere

	gpu::sRenderTarget render_fbo;

	gpu::sRenderTarget buffer_fbo;
	gpu::sTexture t_compose[2], t_depth; ///< 1:1
	gpu::sTexture t_color_aa, t_depth_aa; ///< 1:1

	gpu::sRenderTarget resolve_fbo; ///< For MSAA support.

	gpu::sRenderTarget color_depth_read_fbo;
	gpu::sTexture t_color_read, t_depth_read;

	gpu::sRenderTarget fx_fbo;
	gpu::sTexture t_fx[3], t_fx_depth;
	gpu::sTexture t_gbuffer[4];

	gpu::sShader single_texture_2d_shader, single_texture_color_shader, single_texture_shader, single_color_shader, simple_shader, ambient_shader,
		pointlight_shader, pointlight_shadow_shader, spotlight_shader, spotlight_shadow_shader, linearlight_shader, linearlight_shadow_shader, ds_fog_shader;

	//
	Signal<void(RenderSystem &)> begin_draw_frame_signal;
	Signal<bool(RenderSystem &)> set_render_target_signal;
	Signal<bool(RenderSystem &)> clear_frame_signal;
	Signal<void(RenderSystem &)> frame_cleared_signal;
	Signal<void(RenderSystem &)> renderables_drawn_signal;
	Signal<void(RenderSystem &, RenderPass::Pass)> end_render_pass_signal;
	Signal<void(RenderSystem &)> frame_complete_signal;

	Signal<bool(RenderSystem &, const gpu::sRenderTarget &, const gpu::sTexture &, const gpu::sTexture &)> apply_post_processes_signal;

/*!
	@name Low-level draw
	@{
*/
	/// Select and configure a built-in shader for a simple draw operation.
	bool SetShaderAuto(bool has_color);
	bool SetShaderAuto(bool has_color, const gpu::Texture &);

	/// Draw a set of lines.
	void DrawLine(uint count, const Vector3 *pos, const Color *col = nullptr, const Vector2 *uv = nullptr, const uint16_t *idx = nullptr, uint vtx_count = 0);
	/// Draw a set of triangles.
	void DrawTriangle(uint count, const Vector3 *pos, const Color *col = nullptr, const Vector2 *uv = nullptr, const uint16_t *idx = nullptr, uint vtx_count = 0);
	/// Draw a set of sprites.
	void DrawSprite(uint count, const Vector3 *pos, const Color *col = nullptr, const float *size = nullptr, float global_size = 1.f);

	/// Draw a set of lines using a built-in shader selected by the render system.
	void DrawLineAuto(uint count, const Vector3 *pos, const Color *col = nullptr, const Vector2 *uv = nullptr, const gpu::Texture * = nullptr, const uint16_t *idx = nullptr, uint vtx_count = 0);
	/// Draw a set of triangles using a built-in shader selected by the render system.
	void DrawTriangleAuto(uint count, const Vector3 *pos, const Color *col = nullptr, const Vector2 *uv = nullptr, const gpu::Texture * = nullptr, const uint16_t *idx = nullptr, uint vtx_count = 0);
	/// Draw a set of sprites using a built-in shader selected by the render system.
	void DrawSpriteAuto(uint count, const Vector3 *pos, const gpu::Texture &tex, const Color *col = nullptr, const float *size = nullptr, float global_size = 1.f);

	/// Draw a quad in screen space.
	void DrawQuad2D(const fRect &src, const fRect &dst);
	/// Draw a fullscreen quad.
	void DrawFullscreenQuad(const Vector2 &uv);
/// @}

	/// Draw a geometry using the current shader ignoring its materials and surface shaders.
	void DrawGeometrySimple(const Geometry &geo);
	/// Draw a scene using the current shader ignoring its materials and surface shaders.
	void DrawSceneSimple(const core::Scene &scene);

	bool BeginDrawFrame();
	void DrawRenderables(const IRenderableList &, core::LightSystem &);
	void DrawRenderPassShader(const IRenderableList &, RenderPass::Shader);
	void EndDrawFrame();

	void ApplyPostProcesses(const std::vector<core::sComponent> &post_process_components);

	const gpu::sTexture &GetShadowMap() const { return shadow_map_data.map; }

	/// Return the default raster font object.
	const std::shared_ptr<RasterFont> &GetDefaultFont() const { return default_font; }

private:
	PrimitiveLists prim_lists;

	friend void DrawRenderPrimitives(RenderSystem &render_system, const RenderPrimitive *prims, uint count, const RenderPass &pass);

	gpu::sRenderer renderer;

	std::atomic<bool> is_initialized;

protected:
	friend class PendingTaskGuard;
	std::atomic<uint32_t> pending_tasks;

private:
	Config config;
	Statistics stats;

	TCache<Material> materials;
	TCache<Geometry> geometries;
	TCache<SurfaceShader> surface_shaders;

	RenderTechnique render_technique;

	/// Configure the render system according to the underlying renderer caps.
	void DiscoverConfiguration();

	void LoadCoreShaders(bool support_3d = true);
	void FreeCoreShaders();

	float frame_clock;

	core::VertexLayout simple_vertex_layout;

	DirectVBO direct_vbo;
	ShadowMapData shadow_map_data;

	gpu::sRenderTarget render_target;
	gpu::sTexture t_final;

	Eye eye;
	FrustumPlanes frustum;

	std::shared_ptr<RasterFont> default_font;
};

typedef std::shared_ptr<RenderSystem> sRenderSystem;

//----
class PendingTaskGuard {
public:
	PendingTaskGuard(RenderSystem &render_system) : system(render_system) { ++system.pending_tasks; }
	~PendingTaskGuard() { --system.pending_tasks; }

private:
	RenderSystem &system;
};

/// Draw multiple render primitives.
void DrawRenderPrimitives(RenderSystem &render_system, const RenderPrimitive *prims, uint count, const RenderPass &pass);

/// Given a list of renderable, extract all the render primitives in a given context.
void BuildFrustumPrimitiveLists(const IRenderableList &renderables, const FrustumPlanes &frustum, const Matrix4 &frustum_matrix, const FrustumPlanes &view_frustum, const Matrix4 &view_matrix, PrimitiveLists &primitive_lists, IRenderable::Context ctx = IRenderable::ContextDefault);
/// Call the render system end of pass hooks.
void EmitEndRenderPassSignal(RenderSystem &render_system, RenderPass::Pass pass);

extern RenderSystem *g_render_system;

} // render
} // gs
