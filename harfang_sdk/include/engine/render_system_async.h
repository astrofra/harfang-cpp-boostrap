// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/render_draw.h"
#include "engine/render_system.h"
#include "engine/set_shader_input.h"
#include "engine/renderer.h"
#include "engine/light_system.h"
#include "foundation/call_task.h"

namespace gs {
namespace render {

#define RSA_task_affinity nullptr, render_system->GetRenderer()->GetWorkerAffinity()

class RenderSystemAsync {
	sRenderSystem render_system;

public:
	RenderSystemAsync(sRenderSystem s) : render_system(std::move(s)) {}

	const sRenderSystem &GetRenderSystem() const { return render_system; }

	std::future<RenderSystem::RenderTechnique> GetRenderTechnique() { return run_call_with_return_value<RenderSystem::RenderTechnique>(std::bind(&RenderSystem::GetRenderTechnique, shared_ref(render_system)), RSA_task_affinity); }
	void SetRenderTechnique(RenderSystem::RenderTechnique technique) { run_call<void>(std::bind(&RenderSystem::SetRenderTechnique, shared_ref(render_system), technique), RSA_task_affinity); }

	std::future<iVector2> GetInternalResolution() const { return run_call_with_return_value<iVector2>(std::bind(&RenderSystem::GetInternalResolution, shared_ref(render_system)), RSA_task_affinity); }
	void SetInternalResolution(const iVector2 &resolution) { run_call<void>(std::bind(&RenderSystem::SetInternalResolution, shared_ref(render_system), resolution), RSA_task_affinity); }

	std::future<Vector2> GetViewportToInternalResolutionRatio() const { return run_call_with_return_value<Vector2>(std::bind(&RenderSystem::GetViewportToInternalResolutionRatio, shared_ref(render_system)), RSA_task_affinity); }

	void SetAA(uint sample_count) { render_system->SetAA(sample_count); }

	void SetView(const Matrix4 &view, const Matrix44 &projection, Eye eye = EyeMono) { run_call<void>(std::bind(&RenderSystem::SetView, shared_ref(render_system), view, projection, eye), RSA_task_affinity); }

	std::future<uint> PurgeCache() { return run_call_with_return_value<uint>(std::bind(&RenderSystem::PurgeCache, shared_ref(render_system)), RSA_task_affinity); }
	void RefreshCacheEntry(const char *name) { run_call<void>(std::bind(&RenderSystem::RefreshCacheEntry, shared_ref(render_system), bind_string(name)), RSA_task_affinity); }

	void DrawRasterFontBatch() { run_call<void>(std::bind(&RenderSystem::DrawRasterFontBatch, shared_ref(render_system)), RSA_task_affinity); }

	sMaterial HasMaterial(const char *name) { return render_system->HasMaterial(name); }
	sMaterial LoadMaterial(const char *name, bool use_cache = true) { return render_system->LoadMaterial(name, use_cache); }
	sMaterial LoadMaterial(const char *name, const char *source, DocumentFormat format = DocumentFormatUnknown, bool use_cache = true) { return render_system->LoadMaterial(name, source, format, use_cache); }
	sMaterial CreateMaterial(const core::sMaterial &mat, bool use_cache = true) { return render_system->CreateMaterial(mat, use_cache); }

	sGeometry HasGeometry(const char *name) { return render_system->HasGeometry(name); }
	sGeometry LoadGeometry(const char *name, bool use_cache = true) { return render_system->LoadGeometry(name, use_cache); }
	sGeometry LoadGeometry(const char *name, const char *source, DocumentFormat format = DocumentFormatUnknown, bool use_cache = true) { return render_system->LoadGeometry(name, source, format, use_cache); }
	sGeometry CreateGeometry(const core::sGeometry &geo, bool use_cache = true) { return render_system->CreateGeometry(geo, use_cache); }

	sSurfaceShader HasSurfaceShader(const char *name) { return render_system->HasSurfaceShader(name); }
	sSurfaceShader LoadSurfaceShader(const char *name, bool use_cache = true) { return render_system->LoadSurfaceShader(name, use_cache); }

	//--
	void DrawLine(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<Vector2> *uv = nullptr) {
		run_call<void>(std::bind(&RenderSystem::DrawLine, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<Vector2>(uv ? uv->data() : nullptr, uv ? memory_usage(*uv) : 0), nullptr, 0),
			RSA_task_affinity);
	}

	void DrawTriangle(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<Vector2> *uv = nullptr) {
		run_call<void>(std::bind(&RenderSystem::DrawTriangle, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<Vector2>(uv ? uv->data() : nullptr, uv ? memory_usage(*uv) : 0), nullptr, 0),
			RSA_task_affinity);
	}

	void DrawSprite(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<float> *size = nullptr, float global_size = 1.f) {
		run_call<void>(std::bind(&RenderSystem::DrawSprite, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<float>(size ? size->data() : nullptr, size ? memory_usage(*size) : 0), global_size),
			RSA_task_affinity);
	}

	void DrawLineAuto(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<Vector2> *uv = nullptr, gpu::sTexture texture = nullptr) {
		run_call<void>(std::bind(&RenderSystem::DrawLineAuto, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<Vector2>(uv ? uv->data() : nullptr, uv ? memory_usage(*uv) : 0), shared_ref(texture), nullptr, 0),
			RSA_task_affinity);
	}

	void DrawTriangleAuto(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<Vector2> *uv = nullptr, gpu::sTexture texture = nullptr) {
		run_call<void>(std::bind(&RenderSystem::DrawTriangleAuto, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<Vector2>(uv ? uv->data() : nullptr, uv ? memory_usage(*uv) : 0), shared_ref(texture), nullptr, 0),
			RSA_task_affinity);
	}

	void DrawSpriteAuto(uint count, const std::vector<Vector3> &vtx, const std::vector<Color> *color = nullptr, const std::vector<float> *size = nullptr, gpu::sTexture texture = nullptr, float global_size = 1.f) {
		run_call<void>(std::bind(&RenderSystem::DrawSpriteAuto, shared_ref(render_system), count, memory_block<Vector3>(vtx.data(), memory_usage(vtx)),
						   shared_ref(texture), memory_block<Color>(color ? color->data() : nullptr, color ? memory_usage(*color) : 0),
						   memory_block<float>(size ? size->data() : nullptr, size ? memory_usage(*size) : 0), global_size),
			RSA_task_affinity);
	}

	//--
	void BeginDrawFrame() { run_call<bool>(std::bind(&RenderSystem::BeginDrawFrame, shared_ref(render_system)), RSA_task_affinity); }
	void DrawRenderables(const render::IRenderableList &renderables, const core::sLightSystem &light_system) { run_call<void>(std::bind(&RenderSystem::DrawRenderables, shared_ref(render_system), renderables, shared_ref(light_system)), RSA_task_affinity); }
	void EndDrawFrame() { run_call<void>(std::bind(&RenderSystem::EndDrawFrame, shared_ref(render_system)), RSA_task_affinity); }

	std::future<bool> DrawRenderablesPicking(const render::IRenderableList &renderables, const gpu::sRenderTarget &rt) { return run_call_with_return_value<bool>(std::bind(&render::DrawRenderablesPicking, shared_ref(render_system), renderables, rt), RSA_task_affinity); }

	std::future<bool> Initialize(gpu::sRenderer r, bool support_3d = true) { return run_call_with_return_value<bool>(std::bind(&RenderSystem::Initialize, shared_ref(render_system), r, support_3d), r->GetWorkerAffinity()); }
	std::future<void> Free() { return run_call_with_return_value<void>(std::bind(&RenderSystem::Free, shared_ref(render_system)), RSA_task_affinity); }

	void SetShaderEngineValues() { run_call<void>(std::bind(&render::SetShaderEngineValues, shared_ref(render_system)), RSA_task_affinity); }
};

typedef std::shared_ptr<RenderSystemAsync> sRenderSystemAsync;

} // render
} // gs
