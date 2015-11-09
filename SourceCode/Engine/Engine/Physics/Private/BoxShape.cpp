// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\BoxShape.h>
#include <Private\PhysicsCommon.h>


BEGIN_NAMESPACE


BoxShape::BoxShape(b2PolygonShape *Shape, const Vector2 &HalfSize) :
	m_Shape(Shape),
	m_HalfSize(HalfSize)

{
	m_Type = ST_BOX;
	m_Center = ToVector2(m_Shape->m_centroid);
}


BoxShape::~BoxShape(void)
{
	m_Shape = NULL;
}

void BoxShape::SetCenter(const Vector2 &Center)
{
	m_Center = Center;
	m_Shape->m_centroid = Tob2Vec2(m_Center);
}


void BoxShape::SetHalfSize(const Vector2 &HalfSize)
{
	m_HalfSize = HalfSize;
	m_Shape->SetAsBox(m_HalfSize.X, m_HalfSize.Y);
}


END_NAMESPACE

