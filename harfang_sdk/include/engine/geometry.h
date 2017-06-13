// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "engine/geometry_uv_set.h"
#include "engine/tangent_frame.h"
#include "foundation/color.h"
#include "foundation/matrix4.h"
#include "foundation/minmax.h"
#include "foundation/unit.h"
#include "foundation/vector.h"
#include <array>
#include <memory>

namespace gs {
namespace core {

struct GeometrySkin {
	bool operator==(const GeometrySkin &s) const {
		for (int i = 0; i < 4; ++i)
			if (w[i] != s.w[i] || bone_index[i] != s.bone_index[i])
				return false;
		return true;
	}

	uint8_t w[4];
	uint16_t bone_index[4];
};

struct Polygon {
	uint8_t vtx_count = 0;
	uint8_t material = 0;
	uint *binding = nullptr;
};

struct VertexToPolygon {
	uint16_t pol_count;
	std::vector<uint> pol_index; // polygon index in the geometry
	std::vector<uint> vtx_index; // vertex index in the polygon
};

struct PolygonVertex {
	uint pol_index;
	uint vtx_index;
};

struct VertexToVertex {
	uint16_t vtx_count;
	std::vector<PolygonVertex> vtx;
};

typedef Polygon *pPolygon;

namespace GeometryFlag {
typedef int Type;

static const Type
	Default = 0x0,

	Hidden = 0x01,
	NullLodProxy = 0x02,
	NullShadowProxy = 0x04,

	// non-serialized
	NoMaterialCache = 0x08;
};

//----
class Geometry {
public:
	static const int UVChannelCount = 4;

	std::string name;
	GeometryFlag::Type flag = GeometryFlag::Default;

	std::string lod_proxy;
	float lod_distance = units::Mtr(100.f);

	std::string shadow_proxy;

	/// Return the number of triangles in the mesh.
	uint GetTriangleCount() const {
		uint n, c = 0;
		for (n = 0; n < pol.size(); ++n)
			if (pol[n].vtx_count >= 3)
				c += pol[n].vtx_count - 2;
		return c;
	}

	/*!
		@short Flag vertices sharing the same properties as homogeneous.

		All vertices attributes are checked and compared. If they all lie
		under a given threshold then the vertex is reported as homogeneous.
		This function is heavily used by the geometry stripper and triangle
		list builder.

		@param material_index	Optionally restrict attribute comparison
								to one material only.
								(default: -1 to include all materials in
								the geometry.)
	*/
	void FlagHomogeneousVertex(std::vector<char> &flag, const std::vector<uint> &polygon_index, const std::vector<VertexToPolygon> &, int material_index = -1) const;

/*!
	@name Topology section
	@{
*/
	/// Compute the local geometry bounding box.
	MinMax ComputeLocalMinMax() const;
	/// Compute geometry bones bounding volumes.
	bool ComputeLocalBoneMinMax(std::vector<MinMax> &bone_minmax) const;

	std::vector<Vector3> vtx, vtx_normal;
	std::vector<TangentFrame> vtx_tangent;
	std::vector<Color> rgb;
	std::array<UVSet, UVChannelCount> uv;

	std::vector<Polygon> pol;
	std::vector<uint> binding;

	void AllocateVertex(uint count);
	void AllocatePolygon(uint count);

	/// Allocate polygon binding array.
	bool AllocatePolygonBinding();
	/// Compute polygon binding count.
	uint ComputePolygonBindingCount() const;
/// @}

/*!
	@name API handcraft geometry
	@{
*/
	bool SetName(const char *name);

	void AllocateVertexNormal(uint count);
	void AllocateVertexTangent(uint count);
	void AllocateRgb(uint count);
	void AllocateMaterialTable(uint count);
	bool AllocateUVChannels(uint channel_count, uint uv_per_channel);

	int GetVertexCount() const { return vtx.size(); }
	int GetPolygonCount() const { return pol.size(); }
	int GetVertexNormalCount() const { return vtx_normal.size(); }
	int GetVertexTangentCount() const { return vtx_tangent.size(); }
	int GetRgbCount() const { return rgb.size(); }
	int GetUVCount() const;

	bool SetVertex(uint index, const gs::Vector3 &vertex);
	Vector3 GetVertex(uint index) const;
	bool SetVertexNormal(uint index, const Vector3 &vertex);
	Vector3 GetVertexNormal(uint index) const;
	bool SetRgb(uint poly_index, uint count, const Color *colors);
	bool SetRgb(uint poly_index, std::vector<Color> &colors);
	Color GetRgb(uint index) const;
	bool SetUV(uint channel, uint poly_index, uint count, const Vector2 *uvs);
	bool SetUV(uint channel, uint poly_index, std::vector<Vector2> &uvs);
	Vector2 GetUV(uint channel, uint index) const;

	bool SetPolygonVertexCount(uint index, uint8_t vtx_count);
	bool SetPolygonMaterialIndex(uint index, uint8_t material);
	bool SetPolygon(uint index, uint8_t vtx_count, uint8_t material);
	int GetPolygonVertexCount(uint index) const;
	int GetPolygonMaterialIndex(uint index) const;

	bool SetPolygonBinding(uint index, uint count, const int *idx);
	bool SetPolygonBinding(uint index, std::vector<int> &idx);

	float ComputePolygonArea(uint index) const;

	bool Validate() const;
/// @}

/*!
	@name Skinning section
	@{
*/
	/// Allocate bones array (not the skin weights array).
	void AllocateBone(uint bone_count);
	/// Return the number of bones referenced by the geometry.
	uint GetBoneCount() const;

	std::vector<std::string> bone_name;
	std::vector<Matrix4> bone_bind_matrix;

	std::vector<GeometrySkin> skin; ///< skin weights
/// @}

	std::vector<Vector3> pol_normal;
	std::vector<TangentFrame> pol_tangent;

	bool ComputePolygonNormal(bool force = false);
	bool ComputePolygonTangent(uint uv_index = 0, bool force = false);

	bool ComputeVertexNormal(float msa = 0.7f, bool force = false);
	bool ComputeVertexNormal(std::vector<Vector3> &normal_out, float msa = 0.7f);
	bool ComputeVertexTangent(bool reverse_T = false, bool reverse_B = false, bool force = false);

	void ReverseTangentFrame(bool reverse_T, bool reverse_B);

	/*!
	@name Geometry tools
	@{
*/
	/// Compute polygon start index.
	void ComputePolygonIndex(std::vector<uint> &index_out) const;
	/// Compute vertex to polygon table.
	void ComputeVertexToPolygon(std::vector<VertexToPolygon> &vtx_to_poly) const;
	/// Compute vertex to vertex table.
	void ComputeVertexToVertex(std::vector<VertexToVertex> &vtx_to_vtx, const std::vector<VertexToPolygon> *vtx_to_poly = nullptr) const;
	/// @}

	void SmoothRGB(uint pass_count, float max_smooth_angle);

/*!
	@name Material section
	@{
*/
	std::vector<std::string> materials;

	/// Merge duplicate materials in table.
	uint MergeDuplicateMaterials();
/// @}
};

/// Compute the minmax of a vertex array.
bool ComputeVertexArrayMinMax(uint count, const Vector3 *vtx, MinMax &minmax, const Matrix4 *transform = nullptr);

typedef std::shared_ptr<Geometry> sGeometry;

} // core
} // gs
