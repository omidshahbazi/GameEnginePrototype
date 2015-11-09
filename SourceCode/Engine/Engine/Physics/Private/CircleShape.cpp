// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\CircleShape.h>
#include <Private\PhysicsCommon.h>


BEGIN_NAMESPACE


CircleShape::CircleShape(b2CircleShape *Shape) :
	m_Shape(Shape)
{
	m_Type = ST_CIRCLE;
	m_Radius = m_Shape->m_radius;
	m_Center = ToVector2(m_Shape->m_p);
}


CircleShape::~CircleShape(void)
{
	m_Shape = NULL;
}


void CircleShape::SetCenter(const Vector2 &Center)
{
	m_Center = Center;
	m_Shape->m_p = Tob2Vec2(m_Center);

}


void CircleShape::SetRadius(float32 Value)
{
	m_Radius = Value;
	m_Shape->m_radius = Value;
}


END_NAMESPACE

