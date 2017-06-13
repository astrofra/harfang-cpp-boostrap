// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/resource.h"
#include "foundation/task.h"
#include "foundation/rect.h"

namespace gs {
namespace gpu {

namespace TextureUsage {
	typedef int Type;
	static const Type IsRenderTarget = 0x01, IsShaderResource = 0x02;
	static const Type Default = IsShaderResource;
}

/// GPU Texture
struct Texture : public Resource {
	union NativeId {
		int32_t i32;
		int64_t i64;
		void *void_p = nullptr;
	};

	enum Format : uint8_t {
		RGBA8,  ///< 4 channels 8 bit integer texture
		BGRA8,  ///< 4 channels 8 bit integer texture
		RGBA16, ///< 4 channels 16 bit integer texture
		RGBAF,  ///< 4 channels float texture
		Depth,  ///< integer depth texture
		DepthF, ///< float depth texture
		R8,		///< single channel 8 bit integer texture
		R16,	///< single channel 16 bit integer texture
		InvalidFormat
	};

	enum AA : uint8_t { NoAA, MSAA2x, MSAA4x, MSAA8x, MSAA16x, AALast };

	explicit Texture(const char *name = "Texture");

	uint GetWidth() const { return width; }
	uint GetHeight() const { return height; }
	uint GetDepth() const { return depth; }

	fRect GetRect() const { return fRect(0, 0, float(width), float(height)); }

	virtual NativeId GetNativeId() const { return NativeId(); }

	// FIXME these should not be cached! calling for bugs here!
	uint16_t width, height, depth;
	Format format;
	AA aa;

	bool is_rtt : 1;
	bool has_mipmap : 1;
};

/// Return the texture format pixel size in bytes.
size_t GetTextureFormatPixelSize(Texture::Format format);

typedef std::shared_ptr<Texture> sTexture;

class Renderer;

void TextureDeleter(Texture *texture, std::weak_ptr<Renderer> renderer_weak, task_affinity worker);

} // gpu
} // gs
