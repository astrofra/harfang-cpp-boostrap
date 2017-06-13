// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/font_engine.h"
#include "foundation/matrix3.h"
#include "foundation/vector4.h"
#include "foundation/vector.h"
#include <memory>

#undef DrawText

namespace gs {

struct IPictureRenderer;

// A two dimensional array of colors.
class Picture {
public:
	/// Supported picture pixel formats.
	enum Format { Gray8, Gray16, GrayF, RGB555, RGB565, RGB8, BGR8, RGBA8, BGRA8, ARGB8, ABGR8, RGB16, BGR16, RGBA16, BGRA16, ARGB16, ABGR16, RGBF, BGRF, RGBAF, BGRAF,ARGBF, ABGRF, InvalidFormat };

	enum BrushMode { BrushNone, BrushSolid };
	enum PenMode { PenNone, PenSolid };
	enum PenCap { ButtCap, SquareCap, RoundCap };
	enum LineJoin { MiterJoin, MiterJoinRevert, RoundJoin, BevelJoin, MiterJoinRound };
	enum InnerJoin { InnerBevel, InnerMiter, InnerJag, InnerRound };

	enum Filter { Nearest, Bilinear, Hanning, Hamming, Hermite, Quadric, Bicubic, Kaiser, Catrom, Mitchell, Spline16, Spline36, Gaussian, Bessel, Sinc36, Sinc64, Sinc256, Lanczos36, Lanczos64, Lanczos256, Blackman36, Blackman64, Blackman256 };

	template <typename T> friend struct AGGRenderer; // antigrain geometry renderer

	Picture();
	Picture(uint width, uint height, Format format, const void *data = nullptr);
	Picture(const Picture &source);
	~Picture();

	uint GetWidth() const { return width; }
	uint GetHeight() const { return height; }
	Vector2 GetCenter() const { return Vector2(float(width) * 0.5f, float(height) * 0.5f); }
	size_t GetStride() const;
	Format GetFormat() const { return format; }

	iRect GetRect() const { return iRect(0, 0, width, height); }

	/// Allocate storage for a given picture size and format.
	bool AllocAs(uint width, uint height, Format format);
	/// Allocate storage according to another picture.
	bool AllocAs(const Picture &as) { return AllocAs(as.GetWidth(), as.GetHeight(), as.GetFormat()); }
	/// Free storage.
	void Free();

	/// Perform a copy of an input picture.
	Picture &operator=(const Picture &source);

	/// Return picture raster data.
	uint8_t *GetData() const { return (uint8_t *)data.data(); }
	uint8_t *GetDataAt(int x, int y) const;

	size_t GetDataSize() const { return memory_usage(data); }

	/// Clear the clipping rect.
	void ClearClipping();
	/// Set the clipping rect.
	void SetClipping(int start_x, int start_y, int end_x, int end_y);

	/// Clear the picture with a RGBA color.
	void ClearRGBA(float r, float g, float b, float a = 1.f);
	/// Read a pixel from the picture, return as an RGBA vector.
	Vector4 GetPixelRGBA(int x, int y) const;
	/// Write a RGBA color to the picture.
	void PutPixelRGBA(int x, int y, float r, float g, float b, float a = 1.f);
	/// Blend a RGBA color with the existing content of the picture.
	void BlendPixelRGBA(int x, int y, float r, float g, float b, float a = 1.f);

	void SetFillColorRGBA(float r, float g, float b, float a = 1.f);
	void SetPenColorRGBA(float r, float g, float b, float a = 1.f);

	/// Blit copy a picture.
	bool BlitCopy(const Picture &src, iRect src_rect, iVector2 dst_pos);
	/// Blit a picture.
	bool Blit(const Picture &src, iRect src_rect, iVector2 dst_pos);
	/// Blit part of a picture.
	bool Blit(const Picture &src, iRect src_rect, iRect dst_rect, Filter filter = Bilinear);
	/// Blit a picture with transform.
	bool BlitTransform(const Picture &src, iRect dst_rect, const Matrix3 &matrix, Filter filter = Bilinear);

	/// Flip the picture content.
	void Flip(bool horizontal, bool vertical);
	/// Reframe the picture content.
	bool Reframe(int top, int bottom, int left, int right);
	/// Crop the picture content.
	bool Crop(int start_x, int start_y, int end_x, int end_y);

	/// Resize the picture.
	bool Resize(uint width, uint height, Filter filter = Bilinear);

	/// Convert the picture to a different format.
	bool Convert(Format format);

	void SetFillMode(BrushMode mode);
	void SetPenMode(PenMode mode);
	void SetPenWidth(float width);
	void SetPenCap(PenCap cap);
	void SetLineJoin(LineJoin join);
	void SetInnerJoin(InnerJoin join);

	/// Move the path cursor to an absolute position in pixels.
	void MoveTo(float x, float y);
	/// Define a path line from the current cursor position.
	void LineTo(float x, float y);
	/// Close the current polygon.
	void ClosePolygon();
	/// Add a rounded rectangle to the path.
	void AddRoundedRect(float start_x, float start_y, float end_x, float end_y, float radius);
	/// Add an ellipse to the path.
	void AddEllipse(float x, float y, float radius_x, float radius_y);
	/// Add a circle to the path.
	void AddCircle(float x, float y, float radius);
	/// Draw path.
	void DrawPath();

	/// Draw a line.
	void DrawLine(float start_x, float start_y, float end_x, float end_y);
	/// Draw a rectangle.
	void DrawRect(float start_x, float start_y, float end_x, float end_y);
	/// Draw a rounded rectangle.
	void DrawRoundedRect(float start_x, float start_y, float end_x, float end_y, float radius);
	/// Draw an ellipse.
	void DrawEllipse(float x, float y, float radius_x, float radius_y);
	/// Draw a circle.
	void DrawCircle(float x, float y, float radius) { DrawEllipse(x, y, radius, radius); }

	/// Draw glyph.
	void DrawGlyph(FontEngine &font_engine, std::u32string::value_type glyph_code, float x, float y);
	/// Draw text.
	void DrawText(FontEngine &font_engine, const char *text, float x, float y);

	/// Compare this picture content with the content from another picture.
	bool Compare(const Picture &picture, float threshold = 0.f);

private:
	std::unique_ptr<IPictureRenderer> renderer;

	std::vector<char> data;
	uint16_t width, height;
	Format format : 8;
};

/// Return the pixel size in bytes (bpp/8) of a pixel format.
size_t GetPixelSize(Picture::Format format);
/// Return the number of component in a pixel format.
uint GetComponentCount(Picture::Format format);

typedef std::shared_ptr<Picture> sPicture;

} // gs
