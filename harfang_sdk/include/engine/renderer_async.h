// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/vertex_layout.h"
#include "foundation/cext.h"
#include "foundation/binary_blob.h"
#include "foundation/color.h"
#include "engine/picture.h"
#include "engine/renderer.h"
#include "foundation/call_task.h"

namespace gs {
namespace gpu {

#define RA_task_affinity nullptr, renderer->GetWorkerAffinity()

/// GPU based renderer async interface
class RendererAsync {
public:
	RendererAsync(gpu::sRenderer renderer_, task_affinity affinity = 0) : renderer(renderer_) { renderer->SetWorkerAffinity(affinity); }

	const gpu::sRenderer &GetRenderer() const { return renderer; }

	std::future<uint> PurgeCache() { return run_call_with_return_value<uint>(std::bind(&Renderer::PurgeCache, renderer.get()), RA_task_affinity); }
	void RefreshCacheEntry(const char *name) { run_call<void>(std::bind(&Renderer::RefreshCacheEntry, renderer.get(), bind_string(name)), RA_task_affinity); }

private:
	gpu::sRenderer renderer;

	static void SetRenderTargetColorTexture_adapter(Renderer &r, const sRenderTarget &rt, sTexture tex) { r.SetRenderTargetColorTexture(*rt, &tex, 1); }

	static void ReadRenderTargetColorPixels_adapter(Renderer &r, const sRenderTarget &rt, const sPicture &out, const iRect &rect) {
		out->AllocAs(rect.GetWidth(), rect.GetHeight(), Picture::RGBA8);
		r.ReadRenderTargetColorPixels(rt, out->GetData(), rect);
	}

	/*!
		@name Render target
		@{
	*/
public:
	sRenderTarget NewRenderTarget() { return renderer->NewRenderTarget(); }

	void SetRenderTargetColorTexture(const sRenderTarget &rt, const sTexture &tex) {
		run_call<void>(std::bind(&RendererAsync::SetRenderTargetColorTexture_adapter, shared_ref(renderer), rt, tex), RA_task_affinity);
	}

	void SetRenderTargetDepthTexture(const sRenderTarget &rt, const sTexture &tex) {
		run_call<void>(std::bind(&Renderer::SetRenderTargetDepthTexture, renderer, shared_ref(rt), tex), RA_task_affinity);
	}

	void BlitRenderTarget(const sRenderTarget &src_rt, const sRenderTarget &dst_rt, const iRect &src, const iRect &dst, bool color = true, bool depth = true) {
		run_call<void>(std::bind(&Renderer::BlitRenderTarget, shared_ref(renderer), src_rt, dst_rt, src, dst, color, depth), RA_task_affinity);
	}

	void ReadRenderTargetColorPixels(const sRenderTarget &rt, const sPicture &out, const iRect &rect) {
		run_call<void>(std::bind(&RendererAsync::ReadRenderTargetColorPixels_adapter, shared_ref(renderer), rt, out, rect), RA_task_affinity);
	}

	void ClearRenderTarget() { run_call<void>(std::bind(&Renderer::ClearRenderTarget, shared_ref(renderer)), RA_task_affinity); }
	void SetRenderTarget(const sRenderTarget &rt) { run_call<void>(std::bind(&Renderer::SetRenderTarget, shared_ref(renderer), rt), RA_task_affinity); }

	std::future<bool> CheckRenderTarget() {
		return run_call_with_return_value<bool>(std::bind(&Renderer::CheckRenderTarget, shared_ref(renderer)), RA_task_affinity);
	}

	std::future<bool> CreateRenderTarget(const sRenderTarget &rt) {
		return run_call_with_return_value<bool>(std::bind(&Renderer::CreateRenderTarget, shared_ref(renderer), shared_ref(rt)), RA_task_affinity);
	}

	void FreeRenderTarget(const sRenderTarget &rt) {
		run_call<void>(std::bind(&Renderer::FreeRenderTarget, shared_ref(renderer), shared_ref(rt)), RA_task_affinity);
	}

	/*!
		@name Buffer
		@{
	*/
private:
	static bool CreateBuffer_adapter(Renderer &r, const sBuffer &vbo, BinaryBlob &data, Buffer::Type type, Buffer::Usage usage) {
		return r.CreateBuffer(*vbo, data.GetData(), data.GetDataSize(), type, usage);
	}

	static bool UpdateBuffer_adapter(Renderer &r, const sBuffer &vbo, BinaryBlob &data, size_t start = 0) {
		return r.UpdateBuffer(*vbo, data.GetData(), start, data.GetDataSize());
	}

public:
	sBuffer NewBuffer() { return renderer->NewBuffer(); }

	std::future<size_t> GetBufferSize(sBuffer buf) {
		return run_call_with_return_value<size_t>(std::bind(&Renderer::GetBufferSize, shared_ref(renderer), shared_ref(buf)), RA_task_affinity);
	}

	std::future<void *> MapBuffer(sBuffer buf) {
		return run_call_with_return_value<void *>(std::bind(&Renderer::MapBuffer, shared_ref(renderer), shared_ref(buf)), RA_task_affinity);
	}

	void UnmapBuffer(sBuffer buf) { run_call<void>(std::bind(&Renderer::UnmapBuffer, shared_ref(renderer), shared_ref(buf)), RA_task_affinity); }

	std::future<bool> UpdateBuffer(sBuffer buf, const void *p, size_t start = 0, size_t size = 0) {
		return run_call_with_return_value<bool>(std::bind(&RendererAsync::UpdateBuffer_adapter, shared_ref(renderer), buf, BinaryBlob(p, size), start),
			RA_task_affinity);
	}

	std::future<bool> CreateBuffer(sBuffer buf, const void *data, size_t size, Buffer::Type type, Buffer::Usage usage = Buffer::Static) {
		return run_call_with_return_value<bool>(std::bind(&RendererAsync::CreateBuffer_adapter, shared_ref(renderer), buf, BinaryBlob(data, size), type, usage),
			RA_task_affinity);
	}

	std::future<bool> CreateBuffer(sBuffer buf, const BinaryBlob &data, Buffer::Type type, Buffer::Usage usage = Buffer::Static) {
		return run_call_with_return_value<bool>(std::bind(&RendererAsync::CreateBuffer_adapter, shared_ref(renderer), buf, data, type, usage), RA_task_affinity);
	}

	void FreeBuffer(sBuffer buf) { run_call<void>(bind(&Renderer::FreeBuffer, shared_ref(renderer), shared_ref(buf)), RA_task_affinity); }

	/*!
	@name Texture
	@{
*/
private:
	static void BlitTexture1(Renderer &r, Texture &t, const BinaryBlob &data, uint w, uint h, uint x, uint y) {
		r.BlitTexture(t, data.GetData(), data.GetDataSize(), w, h, x, y);
	}

	static bool CreateTexture1(Renderer &r, Texture &t, int w, int h, Texture::Format f, Texture::AA aa, TextureUsage::Type type, bool mip) {
		return r.CreateTexture(t, nullptr, 0, w, h, f, aa, type, mip);
	}

	static bool CreateTexture2(Renderer &r, Texture &t, Picture &p, TextureUsage::Type type, bool mip) { return r.CreateTexture(t, p, type, mip); }

	static bool CreateTexture3(Renderer &r, Texture &t, BinaryBlob &data, int w, int h, Texture::Format f, Texture::AA aa, TextureUsage::Type type, bool mip) {
		return r.CreateTexture(t, data.GetData(), data.GetDataSize(), w, h, f, aa, type, mip);
	}

public:
	sTexture NewTexture(const char *name = "Texture") { return renderer->NewTexture(name); }

	sTexture NewShadowMap(int width, int height, const char *name = "Shadow") {
		return run_call_with_return_value<sTexture>(
			std::bind(&Renderer::NewShadowMap, shared_ref(renderer), width, height, name), RA_task_affinity).get();
	}

	std::future<bool> CreateTexture(sTexture tex, int width, int height, Texture::Format format = Texture::RGBA8, Texture::AA aa = Texture::NoAA,
		TextureUsage::Type usage = TextureUsage::Default, bool mipmapped = true) {
		return run_call_with_return_value<bool>(
			std::bind(&RendererAsync::CreateTexture1, shared_ref(renderer), shared_ref(tex), width, height, format, aa, usage, mipmapped), RA_task_affinity);
	}

	std::future<bool> CreateTexture(sTexture tex, BinaryBlob &data, int width, int height, Texture::Format format = Texture::RGBA8, Texture::AA aa = Texture::NoAA,
		TextureUsage::Type usage = TextureUsage::Default, bool mipmapped = true) {
		return run_call_with_return_value<bool>(
			std::bind(&RendererAsync::CreateTexture3, shared_ref(renderer), shared_ref(tex), data, width, height, format, aa, usage, mipmapped), RA_task_affinity);
	}

	void FreeTexture(sTexture tex) { run_call<void>(std::bind(&Renderer::FreeTexture, shared_ref(renderer), shared_ref(tex)), RA_task_affinity); }

	void BlitTexture(sTexture tex, const BinaryBlob &data, uint width, uint height, uint x = 0, uint y = 0) {
		run_call<void>(std::bind(&RendererAsync::BlitTexture1, shared_ref(renderer), shared_ref(tex), data, width, height, x, y), RA_task_affinity);
	}

	void ResizeTexture(sTexture tex, uint w, uint h) {
		run_call<void>(std::bind(&Renderer::ResizeTexture, shared_ref(renderer), shared_ref(tex), w, h), RA_task_affinity);
	}

	void BlitTextureBackground(gpu::sTexture tex, const BinaryBlob &data, uint w, uint h, uint x = 0, uint y = 0,
		BackgroundTextureBlit::Type flags = BackgroundTextureBlit::Default) {
		renderer->BlitTextureBackground(tex, data.GetData(), data.GetDataSize(), w, h, x, y, flags);
	}

	std::future<bool> CaptureTexture(sTexture tex, sPicture out) {
		return run_call_with_return_value<bool>(std::bind(&Renderer::CaptureTexture, shared_ref(renderer), shared_ref(tex), shared_ref(out)), RA_task_affinity);
	}

	void GenerateTextureMipmap(sTexture tex) {
		run_call<void>(bind(&Renderer::GenerateTextureMipmap, shared_ref(renderer), shared_ref(tex)), RA_task_affinity);
	}

	std::future<bool> CreateTexture(sTexture tex, sPicture p, TextureUsage::Type usage = TextureUsage::Default, bool mipmapped = true) {
		return run_call_with_return_value<bool>(
			std::bind(&RendererAsync::CreateTexture2, shared_ref(renderer), shared_ref(tex), shared_ref(p), usage, mipmapped), RA_task_affinity);
	}

	sTexture LoadTexture(const char *url, bool use_cache = true) { return renderer->LoadTexture(url, use_cache); }

	const char *GetNativeTextureExt() const { return renderer->GetNativeTextureExt(); }

	/*!
		@name Shader
		@{
	*/
private:
	static void SetShaderValue_adapter0(gpu::Renderer &r, const char *name, int v) { r.SetShaderInt(r.GetShaderVariable(name), &v); }
	static void SetShaderValue_adapter1(gpu::Renderer &r, const char *name, float v) { r.SetShaderFloat(r.GetShaderVariable(name), &v); }
	static void SetShaderValue_adapter2(gpu::Renderer &r, const char *name, const Matrix3 &m) { r.SetShaderMatrix3(r.GetShaderVariable(name), &m); }
	static void SetShaderValue_adapter3(gpu::Renderer &r, const char *name, const Matrix4 &m) { r.SetShaderMatrix4(r.GetShaderVariable(name), &m); }
	static void SetShaderTexture_adapter(gpu::Renderer &r, const char *name, sTexture tex) { r.SetShaderTexture(r.GetShaderVariable(name), *tex); }

	static void SetIndexSource0(gpu::Renderer &r) { r.SetIndexSource(); }
	static void SetIndexSource1(gpu::Renderer &r, gpu::Buffer &b) { r.SetIndexSource(b); }

public:
	sShader LoadShader(const char *path, bool use_cache = true) { return renderer->LoadShader(path, use_cache); }
	sShader LoadShader(const char *name, const char *source, bool use_cache = true) { return renderer->LoadShader(name, source, use_cache); }

	void SetShaderValue(const char *name, int v) {
		run_call<void>(std::bind(&RendererAsync::SetShaderValue_adapter0, shared_ref(renderer), bind_string(name), v), RA_task_affinity);
	}

	void SetShaderValue(const char *name, float v) {
		run_call<void>(std::bind(&RendererAsync::SetShaderValue_adapter1, shared_ref(renderer), bind_string(name), v), RA_task_affinity);
	}

	void SetShaderValue(const char *name, const Matrix3 &m) {
		run_call<void>(std::bind(&RendererAsync::SetShaderValue_adapter2, shared_ref(renderer), bind_string(name), m), RA_task_affinity);
	}

	void SetShaderValue(const char *name, const Matrix4 &m) {
		run_call<void>(std::bind(&RendererAsync::SetShaderValue_adapter3, shared_ref(renderer), bind_string(name), m), RA_task_affinity);
	}

	void SetShaderTexture(const char *name, sTexture tex) {
		run_call<void>(std::bind(&RendererAsync::SetShaderTexture_adapter, shared_ref(renderer), bind_string(name), tex), RA_task_affinity);
	}

	virtual void FreeShader(const gpu::sShader &s) { run_call<void>(std::bind(&Renderer::FreeShader, shared_ref(renderer), shared_ref(s)), RA_task_affinity); }

	/*!
		@name State functions
		@{
	*/
	void SetFillMode(Renderer::FillMode fill_mode) { run_call<void>(std::bind(&Renderer::SetFillMode, shared_ref(renderer), fill_mode), RA_task_affinity); }
	void SetCullFunc(Renderer::CullFunc cull_func) { run_call<void>(std::bind(&Renderer::SetCullFunc, shared_ref(renderer), cull_func), RA_task_affinity); }
	void EnableCulling(bool enable) { run_call<void>(std::bind(&Renderer::EnableCulling, shared_ref(renderer), enable), RA_task_affinity); }

	void SetDepthFunc(Renderer::DepthFunc depth_func) {
		run_call<void>(std::bind(&Renderer::SetDepthFunc, shared_ref(renderer), depth_func), RA_task_affinity);
	}

	void EnableDepthTest(bool enable) { run_call<void>(std::bind(&Renderer::EnableDepthTest, shared_ref(renderer), enable), RA_task_affinity); }
	void EnableDepthWrite(bool enable) { run_call<void>(std::bind(&Renderer::EnableDepthWrite, shared_ref(renderer), enable), RA_task_affinity); }

	void SetBlendFunc(Renderer::BlendFunc src, Renderer::BlendFunc dst) {
		run_call<void>(std::bind(&Renderer::SetBlendFunc, shared_ref(renderer), src, dst), RA_task_affinity);
	}

	void EnableBlending(bool enable) { run_call<void>(std::bind(&Renderer::EnableBlending, shared_ref(renderer), enable), RA_task_affinity); }
	void EnableAlphaToCoverage(bool enable) { run_call<void>(std::bind(&Renderer::EnableAlphaToCoverage, shared_ref(renderer), enable), RA_task_affinity); }
	void SetDefaultStates() { run_call<void>(std::bind(&Renderer::SetDefaultStates, shared_ref(renderer)), RA_task_affinity); }
	void SetIndexSource() { run_call<void>(std::bind(&RendererAsync::SetIndexSource0, shared_ref(renderer)), RA_task_affinity); }

	void SetIndexSource(const sBuffer &vbo) {
		run_call<void>(std::bind(&RendererAsync::SetIndexSource1, shared_ref(renderer), shared_ref(vbo)), RA_task_affinity);
	}

	void SetVertexSource(const sBuffer &vbo, const core::VertexLayout &layout) {
		run_call<void>(std::bind(&Renderer::SetVertexSource, shared_ref(renderer), shared_ref(vbo), layout), RA_task_affinity);
	}

	std::future<sShader> GetShader() { return run_call_with_return_value<sShader>(std::bind(&Renderer::GetShader, shared_ref(renderer)), RA_task_affinity); }

	std::future<bool> SetShader(sShader shader) {
		return run_call_with_return_value<bool>(std::bind(&Renderer::SetShader, shared_ref(renderer), shader), RA_task_affinity);
	}

/*!
	@name Window system
	@{
*/
private:
	static void Set2DMatrices0(gpu::Renderer &r, bool y) { r.Set2DMatrices(y); }

	static void FitViewportToOutputSurface_(gpu::Renderer &r) {
		auto size = r.GetOutputSurfaceSize();
		r.SetViewport(fRect(0, 0, float(size.x), float(size.y)));
	}

public:
	std::future<Surface> NewOutputSurface(const Window &win) {
		return run_call_with_return_value<Surface>(std::bind(&Renderer::NewOutputSurface, shared_ref(renderer), std::ref(win)), RA_task_affinity);
	}
	std::future<Surface> NewOffscreenOutputSurface(int width, int height) {
		return run_call_with_return_value<Surface>(std::bind(&Renderer::NewOffscreenOutputSurface, shared_ref(renderer), width, height), RA_task_affinity);
	}

	void SetOutputSurface(const Surface &srf) {
		run_call<void>(std::bind(&Renderer::SetOutputSurface, shared_ref(renderer), std::ref(srf)), RA_task_affinity);
	}

	void DestroyOutputSurface(Surface &srf) { run_call<void>(std::bind(&Renderer::DestroyOutputSurface, shared_ref(renderer), std::ref(srf)), RA_task_affinity); }

	std::future<Surface> GetOutputSurface() { return run_call_with_return_value<Surface>(std::bind(&Renderer::GetOutputSurface, shared_ref(renderer)), RA_task_affinity); }
	std::future<iVector2> GetOutputSurfaceSize() { return run_call_with_return_value<iVector2>(std::bind(&Renderer::GetOutputSurfaceSize, shared_ref(renderer)), RA_task_affinity); }

	void FitViewportToOutputSurface() { run_call<void>(std::bind(&RendererAsync::FitViewportToOutputSurface_, shared_ref(renderer)), RA_task_affinity); }
/// @}

	std::future<bool> Open(bool debug = false) { return run_call_with_return_value<bool>(std::bind(&Renderer::Open, shared_ref(renderer), debug), RA_task_affinity); }

	std::future<void> Close() { return run_call_with_return_value<void>(std::bind(&Renderer::Close, shared_ref(renderer)), RA_task_affinity); }

	std::future<Matrix4> GetInverseViewMatrix() {
		return run_call_with_return_value<Matrix4>(std::bind(&Renderer::GetInverseViewMatrix, shared_ref(renderer)), RA_task_affinity);
	}

	std::future<Matrix4> GetInverseWorldMatrix() {
		return run_call_with_return_value<Matrix4>(std::bind(&Renderer::GetInverseWorldMatrix, shared_ref(renderer)), RA_task_affinity);
	}

	void SetViewMatrix(const Matrix4 &view) { run_call<void>(std::bind(&Renderer::SetViewMatrix, shared_ref(renderer), view), RA_task_affinity); }

	std::future<Matrix4> GetViewMatrix() {
		return run_call_with_return_value<Matrix4>(std::bind(&Renderer::GetViewMatrix, shared_ref(renderer)), RA_task_affinity);
	}

	void SetProjectionMatrix(const Matrix44 &projection) {
		run_call<void>(std::bind(&Renderer::SetProjectionMatrix, shared_ref(renderer), projection), RA_task_affinity);
	}

	std::future<Matrix44> GetProjectionMatrix() {
		return run_call_with_return_value<Matrix44>(std::bind(&Renderer::GetProjectionMatrix, shared_ref(renderer)), RA_task_affinity);
	}

	void SetWorldMatrix(const Matrix4 &world) { run_call<void>(std::bind(&Renderer::SetWorldMatrix, shared_ref(renderer), world), RA_task_affinity); }

	std::future<Matrix4> GetWorldMatrix() {
		return run_call_with_return_value<Matrix4>(std::bind(&Renderer::GetWorldMatrix, shared_ref(renderer)), RA_task_affinity);
	}

	void SetIdentityMatrices() { run_call<void>(std::bind(&Renderer::SetIdentityMatrices, shared_ref(renderer)), RA_task_affinity); }
	void Set2DMatrices(bool reverse_y = true) { run_call<void>(std::bind(&RendererAsync::Set2DMatrices0, shared_ref(renderer), reverse_y), RA_task_affinity); }

	void ClearClippingPlane() { run_call<void>(bind(&Renderer::ClearClippingPlane, shared_ref(renderer)), RA_task_affinity); }

	void SetClippingPlane(const Vector3 &p, const Vector3 &n) {
		run_call<void>(bind(&Renderer::SetClippingPlane, shared_ref(renderer), p, n), RA_task_affinity);
	}

private:
	bool CaptureFramebuffer_adapter(Picture &p) { return renderer->CaptureFramebuffer(p); }

	std::future<void> last_end_frame_future;

public:
	void ClearClippingRect() { run_call<void>(std::bind(&Renderer::ClearClippingRect, shared_ref(renderer)), RA_task_affinity); }
	void SetClippingRect(const fRect &clipping_rect) {
		run_call<void>(std::bind(&Renderer::SetClippingRect, shared_ref(renderer), clipping_rect), RA_task_affinity);
	}
	std::future<Rect<float>> GetClippingRect() {
		return run_call_with_return_value<Rect<float>>(std::bind(&Renderer::GetClippingRect, shared_ref(renderer)), RA_task_affinity);
	}

	void SetViewport(const fRect &viewport_rect) { run_call<void>(std::bind(&Renderer::SetViewport, shared_ref(renderer), viewport_rect), RA_task_affinity); }

	std::future<Rect<float>> GetViewport() {
		return run_call_with_return_value<Rect<float>>(std::bind(&Renderer::GetViewport, shared_ref(renderer)), RA_task_affinity);
	}

	std::future<Vector2> GetAspectRatio() const {
		return run_call_with_return_value<Vector2>(std::bind(&Renderer::GetAspectRatio, shared_ref(renderer)), RA_task_affinity);
	}

	void Clear(Color color, float z = 1.f, Renderer::ClearFunction clear_func = Renderer::ClearAll) {
		run_call<void>(std::bind(&Renderer::Clear, shared_ref(renderer), color, z, clear_func), RA_task_affinity);
	}

	void DrawBuffers(uint index_count, const sBuffer &idx, const sBuffer &vtx, core::VertexLayout &layout, core::IndexType idx_type = core::IndexUShort,
		PrimitiveType prim_type = PrimitiveTriangle) {
		run_call<void>(std::bind(&gpu::DrawBuffers, shared_ref(renderer), index_count, shared_ref(idx), shared_ref(vtx), layout, idx_type, prim_type),
			RA_task_affinity);
	}

	void DrawFrame() { run_call<void>(std::bind(&Renderer::DrawFrame, shared_ref(renderer)), RA_task_affinity); }
	void ShowFrame() { run_call<void>(std::bind(&Renderer::ShowFrame, shared_ref(renderer)), RA_task_affinity); }

	/// Synchronize with the rendering thread. Return false if the operation timed out, true if synchronization was successful.
	bool Sync(int timeout_ms = 1000) {
		if (last_end_frame_future.valid()) {
			if (last_end_frame_future.wait_for(std::chrono::milliseconds(timeout_ms)) == std::future_status::timeout) {
				debug("Timeout while waiting for rendering thread synchronization");
				return false;
			}
		}
		return true;
	}

	void SetVSync(bool enabled) { run_call<void>(std::bind(&Renderer::SetVSync, shared_ref(renderer), enabled), RA_task_affinity); }

	std::future<bool> CaptureFramebuffer(const sPicture &out) {
		return run_call_with_return_value<bool>(std::bind(&Renderer::CaptureFramebuffer, shared_ref(renderer), shared_ref(out)), RA_task_affinity);
	}
};

typedef std::shared_ptr<RendererAsync> sRendererAsync;

} // gpu
} // gs
