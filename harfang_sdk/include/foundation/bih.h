// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/minmax.h"
#include <memory>
#include <vector>

namespace gs {
namespace bih {

// Bounding interval hierarchy node.
struct Node {
	Node() : axis(3), p(nullptr) {}
	~Node();

	char axis; ///< TODO Packed bitfield!
	void *p; ///< Pointer to child nodes or index array.

	union {
		uint count; ///< Index count in leaf.
		float split[2]; ///< Split planes.
	};
};

struct StackEntry {
	Node *node;
	float tmin, tmax;
};

//
struct Trace {
	explicit Trace(bool closest = true) : stack_pos(0), want_closest(closest), has_i(false), i_t(0.f), node_visited(0) {}

	StackEntry stack[65];
	uint stack_pos;

	bool want_closest;

	bool has_i; ///< Do we have an intersection.
	float i_t; ///< Distance to intersection from ray's origin.
	Vector3 s; ///< Ray origin.
	Vector3 d; ///< Ray direction.

	uint node_visited; ///< Number of nodes visited.
};

/*!
	@short Bounding interval hierarchy

	This is a fully generic bounding interval hierarchy implementation.
	In order to use this structure on a custom set of data you need to derive
	from this class and provide the implementation for the TraceLeaf method.

	In order to build the structure you simply provide a list of volumes to the
	build() methods.
*/
class Tree
{
public:
	Tree();
	virtual ~Tree();

	/// Intersect tree with an axis aligned bounding box.
	uint Intersect(MinMax &minmax, uint *index_array, uint max_index);
	/*
		@short Raytrace hierarchy.
		@note Ray direction must be normalized.
	*/
	virtual void Raytrace(Trace &trace, const Vector3 &s, const Vector3 &d, float l = -1.f, void *parm = nullptr);

	/// Delete hierarchy.
	virtual void Free();

protected:
	/// Minimum leaf volume count.
	uint min_leaf_vcount;

	MinMax minmax; ///< Hierarchy bounding box.
	std::unique_ptr<Node> root; ///< Hierarchy root node.

	std::vector<uint> sarray; ///< Index array.

	uint node_count;
	uint leaf_count;
	uint depth;

/*!
	@name Trace functions
	@{
*/
	/// Trace a leaf.
	virtual void TraceLeaf(Node *leaf, float tmin, float tmax, Trace &trace, void *parm = nullptr) = 0;
/// @}

/*!
	@name Intersection functions
	@{
*/
	/// Intersect a node.
	uint IntersectNode(Node *node, MinMax &sub_mm, uint *index_array, uint max_index);
/// @}

/*!
	@name Build functions
	@{
*/
	/// Create a leaf.
	void MakeNodeLeaf(Node *node, uint count, uint *sarray, MinMax *varray);
	/// Perform a node split.
	void DoNodeSplit(MinMax &minmax, uint count, uint *sarray, MinMax *varray, uint &pivot, Node *node, uint &split_axis);
	/// Split an index list of volumes.
	bool Split(MinMax &minmax, uint count, uint *sarray, MinMax *varray, Node *node, uint depth);

	/// Build hierarchy from a set of input volumes.
	virtual bool Build(uint volume_count, MinMax *varray);
/// @}
};

} // bih
} // gs
