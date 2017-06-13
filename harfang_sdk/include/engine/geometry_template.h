// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include <vector>

#include "engine/geometry.h"

namespace gs {
namespace core {

/*!
	@short Geometry template class.
	@author Thomas Simonnet (scorpheus)
	@author Emmanuel Julien (ejulien@owloh.com)
*/
class GeometryTemplate
{
public:
	static const int max_uv_in_template = 4;

	GeometryTemplate() : merge_threshold(0.0001f) {}

/*!
	@name Polygon declaration
	@{
*/
	void Clear();
	void BeginPolygon();

	void PushVertex(const Vector3 &vertex);
	void PushNormal(const Vector3 &normal);
	void PushUV(uint channel, const Vector2 &uv);
	void PushColor(const Color &color);

	void EndPolygon(uint8_t material_index);

	void ClearMaterials();
	void PushMaterial(const char *path);

	/// Set the vertex merge threshold.
	void SetVertexMergeThreshold(float threshold) { merge_threshold = threshold; }

	/// Instantiate the current template description.
	Geometry *Instantiate(const char *name);

private:
	struct Polygon {
		Polygon() = default;
		Polygon(Polygon &&p) : vertex(std::move(p.vertex)), normal(std::move(p.normal)), color(std::move(p.color)), material(p.material)
		{
			for (int i = 0; i < max_uv_in_template; ++i)
				uv[i] = std::move(p.uv[i]);
		}

		void Clear()
		{
			vertex.clear();
			normal.clear();
			color.clear();
			for (int i = 0; i < max_uv_in_template; ++i)
				uv[i].clear();
			material = 0;
		}

		std::vector<Vector3> vertex;
		std::vector<Vector3> normal;
		std::vector<Color> color;
		std::vector<Vector2> uv[max_uv_in_template];
		uint8_t material;
	};

	struct PolygonVertex {
		uint ipoly;
		uint ivertex;
	};

	Vector3 GetVertex(const PolygonVertex &vtx);
	Vector3 GetNormal(const PolygonVertex &vtx);
	Vector2 GetUV(uint channel, const PolygonVertex &vtx);
	Color GetColor(const Color &color);

	float merge_threshold;

	Polygon polygon;
	std::vector<Polygon> polygons;
	std::vector<std::string> materials;
};

} // core
} // gs

