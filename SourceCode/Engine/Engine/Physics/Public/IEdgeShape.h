// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IEDGESHAPE_H
#define IEDGESHAPE_H

#include <Public\IShape.h>

BEGIN_NAMESPACE

class IEdgeShape : public IShape
{
public:
	virtual ~IEdgeShape(void) {}

	virtual void SetBeginPoint(const Vector2 &Point) = 0;
	virtual const Vector2 &GetBeginPoint(void) const = 0;

	virtual void SetEndPoint(const Vector2 &Point) = 0;
	virtual const Vector2 &GetEndPoint(void) const = 0;
};

END_NAMESPACE
#endif // IEDGESHAPE_H
