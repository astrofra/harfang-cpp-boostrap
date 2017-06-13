// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace gs {
namespace core {

enum ShaderType : uint8_t {
	ShaderNoType,
	ShaderInt,
	ShaderUInt,
	ShaderFloat,
	ShaderVector2,
	ShaderVector3,
	ShaderVector4,
	ShaderMatrix3,
	ShaderMatrix4,
	ShaderTexture2D,
	ShaderTexture3D,
	ShaderTextureCube,
	ShaderTextureShadow,
	ShaderTextureExternal, // for OpenGL ES external OES
	ShaderLastType
};

bool TypeConsumesTextureUnit(ShaderType type);

enum ShaderTypePrecision : uint8_t { ShaderDefaultPrecision, ShaderLowPrecision, ShaderMediumPrecision, ShaderHighPrecision };

struct VertexAttribute {
	enum Semantic : uint8_t {
		Position,
		Normal,
		UV0,
		UV1,
		UV2,
		UV3,
		Color0,
		Color1,
		Color2,
		Color3,
		Tangent,
		Bitangent,
		BoneIndex,
		BoneWeight,
		InstanceModelMatrix,
		InstancePreviousModelMatrix,
		InstancePickingId,
		LastSemantic
	};

	struct SemanticDesc {
		const char *name;
		ShaderType type;
		ShaderTypePrecision precision;
	};

	static const SemanticDesc semantic_desc[LastSemantic];
};

enum TextureUV : uint8_t { TextureUVClamp, TextureUVRepeat, TextureUVMirror, TextureUVCount };
enum TextureFilter : uint8_t { TextureFilterNearest, TextureFilterLinear, TextureFilterTrilinear, TextureFilterAnisotropic, TextureFilterCount };

struct TextureUnitConfig {
	TextureUnitConfig() : wrap_u(TextureUVClamp), wrap_v(TextureUVClamp), wrap_w(TextureUVClamp), min_filter(TextureFilterLinear), mag_filter(TextureFilterLinear) {}
	TextureUnitConfig(TextureUV wrap_u_, TextureUV wrap_v_, TextureFilter min_filter_, TextureFilter mag_filter_) : wrap_u(wrap_u_), wrap_v(wrap_v_), wrap_w(TextureUVClamp), min_filter(min_filter_), mag_filter(mag_filter_) {}

	bool operator==(const TextureUnitConfig &cfg) const {
		return wrap_u == cfg.wrap_u && wrap_v == cfg.wrap_v && wrap_w == cfg.wrap_w && min_filter == cfg.min_filter && mag_filter == cfg.mag_filter;
	}

	TextureUV wrap_u : 2, wrap_v : 2, wrap_w : 2;
	TextureFilter min_filter : 4, mag_filter : 4;
};

extern core::TextureUnitConfig default_texture_unit_config;

struct ShaderValue {
	ShaderValue() { iv[0] = iv[1] = iv[2] = iv[3] = 0; }

	union {
		int32_t iv[4];
		uint32_t uv[4];
		float fv[4];
	};

	std::string path;
	TextureUnitConfig tex_unit_cfg;
};

struct ShaderVariable {
	enum Semantic : uint8_t { // order must stay synchronized with semantic_desc declaration in shader.cpp
		Clock,
		Viewport,
		TechniqueIsForward,
		FxScale,
		InverseInternalResolution,
		InverseViewportSize,
		AmbientColor,
		FogColor,
		FogState,
		DepthBuffer,
		FrameBuffer,
		GBuffer0,
		GBuffer1,
		GBuffer2,
		GBuffer3,

		ViewVector,
		ViewPosition,
		ViewState,

		ModelMatrix,
		InverseModelMatrix,
		NormalMatrix,
		PreviousModelMatrix,
		ViewMatrix,
		InverseViewMatrix,
		ModelViewMatrix,
		NormalViewMatrix,
		ProjectionMatrix,
		ViewProjectionMatrix,
		ModelViewProjectionMatrix,
		InverseViewProjectionMatrix,
		InverseViewProjectionMatrixAtOrigin,

		LightState,
		LightDiffuseColor,
		LightSpecularColor,
		LightShadowColor,
		LightViewPosition,
		LightViewDirection,
		LightShadowMatrix,
		InverseShadowMapSize,
		LightShadowMap,
		LightPSSMSliceDistance,
		ViewToLightMatrix,
		LightProjectionMap,

		BoneMatrix,
		PreviousBoneMatrix,

		PickingId,

		TerrainHeightmap,
		TerrainHeightmapSize,
		TerrainSize,
		TerrainPatchOrigin,
		TerrainPatchSize,

		LastSemantic,

		CategoryGlobalStart = Clock,
		CategoryGlobalEnd = ViewVector,
		CategoryCameraStart = ViewVector,
		CategoryCameraEnd = ModelMatrix,
		CategoryTransformStart = ModelMatrix,
		CategoryTransformEnd = LightState,
		CategoryLightStart = LightState,
		CategoryLightEnd = BoneMatrix,
		CategorySkinningStart = BoneMatrix,
		CategorySkinningEnd = PickingId,
		CategoryNodeStart = PickingId,
		CategoryNodeEnd = TerrainHeightmap,
		CategoryTerrainStart = TerrainHeightmap,
		CategoryTerrainEnd = LastSemantic,
	};

	struct SemanticDesc {
		const char *name;
		ShaderType type;
		ShaderTypePrecision precision;
		uint8_t array_size;
	};

	static const SemanticDesc semantic_desc[LastSemantic];

	ShaderVariable();
	ShaderVariable(const ShaderVariable &var);

	std::string name;
	std::string hint;

	ShaderType type;
	ShaderTypePrecision precision;
	uint8_t array_size;

	std::unique_ptr<ShaderValue> value;
};

enum ShaderStageType : uint8_t {
	ShaderStageVertex, // do not reorder
	ShaderStagePixel,
	ShaderStageLast
};

struct ShaderVarying {
	enum Usage : uint8_t { In, Out };

	ShaderVarying(const char *name, ShaderType type, Usage vertex = Out, Usage pixel = In);

	std::string name;
	ShaderType type;

	Usage usage[ShaderStageLast];
};

/// High-level surface attributes
enum SurfaceAttribute {
	SurfaceNoAttribute = 0x00,

	SurfaceSkinned = 0x01,
	SurfaceIsTerrain = 0x02,
};

/// High-level surface draw state control flags
enum SurfaceDrawState {
	SurfaceDrawDefault = 0x00,

	SurfaceBlendAlpha = 0x01,
	SurfaceBlendAdditive = 0x02,
	SurfaceNoZWrite = 0x04,
	SurfaceNoZTest = 0x08,
	SurfaceAlphaTest = 0x10,
	SurfaceDoubleSided = 0x20,
	SurfaceCastShadow = 0x40,
	SurfaceReceiveShadow = 0x80,
};

/// Shader source for a specific stage
struct ShaderStage {
	std::string global, source;
};

/// Shader variant for a specific platform or shader language
struct ShaderVariant {
	ShaderStage stages[ShaderStageLast];
	std::vector<std::unique_ptr<ShaderVarying>> varyings;
	std::vector<std::string> required_extensions;
};

/// Table of all externally accessible shader variables
struct ShaderVariableTable {
	std::vector<std::unique_ptr<ShaderVariable>> vars;
};

typedef std::shared_ptr<ShaderVariableTable> sShaderVariableTable;

struct Shader : std::enable_shared_from_this<Shader> {
	Shader() : variables(new ShaderVariableTable), surface_attributes(SurfaceNoAttribute), surface_draw_state(SurfaceCastShadow | SurfaceReceiveShadow), alpha_threshold(128) {}

	/// Clone a specific shader variant.
	void Clone(Shader &out, uint8_t variant_index) const;

	std::string name;

	std::shared_ptr<ShaderVariableTable> variables;
	std::vector<std::unique_ptr<ShaderVariant>> variants;

	uint8_t surface_attributes;
	uint8_t surface_draw_state;
	uint8_t alpha_threshold; ///< normalized alpha threshold
};

typedef std::shared_ptr<Shader> sShader;

std::string PreprocessShaderSource(const char *start, const char *end);

} // core
} // gs

namespace std {

string to_string(gs::core::ShaderType type);
string to_string(gs::core::ShaderStageType type);
string to_string(gs::core::VertexAttribute::Semantic semantic);
string to_string(gs::core::ShaderVariable::Semantic semantic);

} // std
