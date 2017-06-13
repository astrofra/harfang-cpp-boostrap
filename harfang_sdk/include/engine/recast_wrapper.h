// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/minmax.h"
#include "foundation/vector3.h"
#include <array>
#include <memory>
#include <vector>

class dtNavMesh;
class dtNavMeshQuery;

namespace gs {
namespace core {

class Geometry;

/// Navigation path
struct NavigationPath {
	std::vector<Vector3> point;
};

/// Navigation layer
struct NavigationLayer {
	bool operator==(const NavigationLayer &layer) const { return radius == layer.radius && height == layer.height && slope == layer.slope; }
	bool operator!=(const NavigationLayer &layer) const { return !(*this == layer); }
	float radius = 0.6f, height = 0.5f, slope = 0.6f;
};

/// Navigation configuration
struct NavigationConfig {
	NavigationConfig();

	bool operator==(const NavigationConfig &config) const {
		if (layers.size() != config.layers.size())
			return false;

		for (uint i = 0; i < layers.size(); ++i)
			if (layers[i] != config.layers[i])
				return false;

		return true;
	}

	std::vector<NavigationLayer> layers;
};

/// Navigation geometry
class NavigationGeometry;

typedef std::shared_ptr<NavigationGeometry> sNavigationGeometry;

class NavigationGeometry {
public:
	struct Layer {
		Layer();
		~Layer();

		dtNavMesh *mesh;
		dtNavMeshQuery *query;
	};

	const NavigationConfig &GetConfig() const { return config; }
	const std::vector<Layer> &GetLayers() const { return layers; }

	const MinMax &GetMinMax() const { return minmax; }

private:
	friend sNavigationGeometry CreateNavigationGeometry(const Geometry &geo, const NavigationConfig &cfg);

	NavigationConfig config;
	std::vector<Layer> layers;

	MinMax minmax;
};

/// Create a navigation geometry.
sNavigationGeometry CreateNavigationGeometry(const Geometry &geo, const NavigationConfig &cfg);

/// Perform a path query.
bool FindNavigationPathTo(const Vector3 &from, const Vector3 &to, dtNavMeshQuery *query, NavigationPath &path);

} // core
} // gs
