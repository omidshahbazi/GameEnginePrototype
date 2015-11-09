// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include <Public\Physics\IPolygonShape.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class PolygonShape : public IPolygonShape
{
public:
	PolygonShape(b2PolygonShape *Shape);
	~PolygonShape(void)
	{
		m_Shape = NULL;
	}

	const Vector2 &GetCenter(void) const
	{
		return m_Center;
	}

	const List<Vector2> &GetVertices(void) const
	{
		return m_Vertices;
	}

	uint32 GetVertexCount(void) const
	{
		return m_VertexCount;
	}

private:
	b2PolygonShape *m_Shape;

	unsigned int m_VertexCount;

	List<Vector2> m_Vertices;
	Vector2 m_Center;
};

END_NAMESPACE
#endif // POLYGONSHAPE_H
