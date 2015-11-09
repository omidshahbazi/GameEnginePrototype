// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPOLYGONSHAPE_H
#define IPOLYGONSHAPE_H

#include <Public\IShape.h>

BEGIN_NAMESPACE

class IPolygonShape : public IShape
{
public:
	virtual ~IPolygonShape(void) {}

	virtual const Vector2 &GetCenter(void) const = 0;

	virtual const List<Vector2> &GetVertices(void) const = 0;

	virtual uint32 GetVertexCount(void) const = 0;
};

END_NAMESPACE
#endif // IPOLYGONSHAPE_H
