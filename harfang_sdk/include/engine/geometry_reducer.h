// Harfang - Copyright 2001-2017 Emmanuel Julien. All Rights Reserved.

#pragma once

#include "foundation/vector3.h"

namespace gs {
namespace core {

class Geometry;

struct nLLEDGE
{
	uint a, b;
	nLLEDGE *p, *n;
};

struct nEENTRY
{
	nLLEDGE *edge;
	nEENTRY *n;
};

typedef nEENTRY *pnEENTRY;

class nEDGELIST
{
public:
	pnEENTRY *lut;
	nLLEDGE *root;
	uint vtx_count, nedg;

	void SetVertexCount(uint);
	void Add(uint, uint);
	void Remove(nLLEDGE *);
	void RemapEdges(uint, uint);
	nLLEDGE *GetEdge(uint, uint);

	nEDGELIST();
	~nEDGELIST();
};

class nLLTRI
{
public:
	uint a, b, c;
	uint8_t m;
	Vector3 normal;
	nLLTRI *p, *n;

	char UseVertex(uint);
	void ReplaceVertex(uint, uint);
};

struct nTENTRY
{
	nLLTRI *tri;
	nTENTRY *n;
};

typedef nTENTRY *pnTENTRY;

class nLTRILIST
{
public:
	pnTENTRY *lut;
	nLLTRI *root;
	Geometry *sg;

	void SetGeo(Geometry *);
	nLLTRI *Add(uint, uint, uint);
	void ReplaceVertex(uint, uint);
	void AddTriToVertex(nLLTRI *, uint);
	void RemoveTriFromVertex(nLLTRI *t, uint v);
	void Remove(nLLTRI *);
	void ComputeNormal(nLLTRI *);

	uint ntri;

	nLTRILIST();
	~nLTRILIST();
};

struct nLVERTEX
{
	char active, locked;
	float cost;
	uint tgtcollapse;
};

class GeometryReducer
{
public:
	nEDGELIST elist;
	nLTRILIST tlist;
	nLVERTEX *vlist;

	void RemoveVertex(uint v);
	void ComputeVertexCost(Geometry *, uint);
	float ComputeEdgeCost(Geometry *, nLLEDGE *);
	Geometry *Reduce(Geometry *, float k);
	char IsBorder(uint v);
};

} // core
} // gs
