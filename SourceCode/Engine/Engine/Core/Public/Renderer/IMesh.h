// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMESH_H
#define IMESH_H

#include <Public\Resource.h>
#include <Public\Renderer\Vertex.h>

BEGIN_NAMESPACE

struct BoundingSphere;

enum class IndexDataAlignments
{
	Bit16 = 0,
	Bit32
};

enum class PrimitiveTypes
{
	Points = 0,
	LineStrip,
	LineLoop,
	Lines,
	TriangleStrip,
	TriangleFan,
	Triangles,
	QuadStrip,
	Quads,
	Polygon,
	PointStrip
};

enum class BasicShapes
{
	Quad = 0,
	Cube
};

class IMesh : public Resource
{
public:
	virtual ~IMesh(void) {}

	virtual void SetVertices(const Vertex *Vertices) = 0;
	virtual void SetIndices(const void *Indices) = 0;

	virtual const BoundingSphere &GetBoundingSphere(void) const = 0;
};

END_NAMESPACE
#endif // IMESH_H
