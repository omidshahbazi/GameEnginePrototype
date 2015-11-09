// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\EdgeShape.h>
#include <Private\PhysicsCommon.h>


BEGIN_NAMESPACE


EdgeShape::EdgeShape(b2EdgeShape *Shape) :
	m_Shape(Shape)

{
	m_Type = ST_EDGE;
	m_Begin = ToVector2(m_Shape->m_vertex1);
	m_End = ToVector2(m_Shape->m_vertex2);
}


EdgeShape::~EdgeShape(void)
{
	m_Shape = NULL;
}


void EdgeShape::SetBeginPoint(const Vector2 &Point)
{
	m_Begin = Point;
	m_Shape->m_vertex1 = Tob2Vec2(m_Begin);
}


void EdgeShape::SetEndPoint(const Vector2 &Point)
{
	m_End = Point;
	m_Shape->m_vertex2 = Tob2Vec2(m_End);
}


END_NAMESPACE

