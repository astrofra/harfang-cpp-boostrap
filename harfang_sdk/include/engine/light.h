// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/color.h"
#include "foundation/frustum.h"
#include "foundation/matrix4.h"
#include "foundation/matrix44.h"
#include "engine/render_primitive.h"
#include "engine/texture.h"
#include "engine/component.h"

namespace gs {
namespace core {

/// Light component
class Light : public std::enable_shared_from_this<Light>, public Component {
public:
	friend class LightSystem;

	decl_component_defaults(Light, "Light");

	Light();

	enum Model { Model_Point, Model_Linear, Model_Spot, Model_Last };
	enum Shadow { Shadow_None, Shadow_ProjectionMap, Shadow_Map };

	comp_decl_member_get_sync_set_async(Light, Model, Model, model);
	comp_decl_member_get_sync_set_async(Light, Shadow, Shadow, shadow);
	comp_decl_member_get_sync_set_async(Light, bool, ShadowCastAll, shadow_cast_all);
	comp_decl_member_get_sync_set_async_validated(Light, float, ShadowRange, shadow_range, ClampToZero);
	comp_decl_member_get_sync_set_async_validated(Light, float, ShadowBias, shadow_bias, ClampToZero);
	comp_decl_member_get_sync_set_async_validated(Light, Vector4, ShadowSplit, shadow_split, ClampVector4ToZeroOne);
	comp_decl_member_get_sync_set_async_validated(Light, float, ZNear, z_near, ZNearValidator);

	comp_decl_member_get_sync_noimpl_set_async_validated(Light, float, Range, range, ClampToZero);
	comp_decl_member_get_sync_set_async_validated(Light, float, ClipDistance, clip_distance, ClampToZero);

	comp_decl_member_get_sync_set_async(Light, Color, DiffuseColor, diffuse_color);
	comp_decl_member_get_sync_set_async(Light, Color, SpecularColor, specular_color);
	comp_decl_member_get_sync_set_async(Light, Color, ShadowColor, shadow_color);

	comp_decl_member_get_sync_set_async(Light, float, DiffuseIntensity, diffuse_intensity);
	comp_decl_member_get_sync_set_async(Light, float, SpecularIntensity, specular_intensity);
	comp_decl_member_get_sync_set_async_validated(Light, float, ConeAngle, cone_angle, ConeAngleValidator);
	comp_decl_member_get_sync_set_async_validated(Light, float, EdgeAngle, edge_angle, EdgeAngleValidator);

	comp_decl_member_get_sync_set_async(Light, gpu::sTexture, ProjectionTexture, projection_texture);

	std::shared_ptr<Component> shared_from_base() override { return shared_from_this(); }

	float GetCullRange() const;

	struct ShadowData {
		render::PrimitiveLists prim_lists;

		fRect rect;
		FrustumPlanes frustum_planes;
		Matrix4 world;
		Matrix44 projection, projection_to_map;

		float slice_distance;
	};

	std::vector<ShadowData> shadow_data;

private:
	static float ZNearValidator(Light *l, float v) { return l->GetRange() > 0.001f ? types::Clamp(v, 0.001f, l->GetRange()) : v; }
	static float ConeAngleValidator(Light *l, float v) { return types::Clamp(v, 0.f, math::Pi * 0.5f - l->GetEdgeAngle()); }
	static float EdgeAngleValidator(Light *l, float v) { return types::Clamp(v, 0.f, math::Pi * 0.5f - l->GetConeAngle()); }
};

} // core
} // gs
