// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\BoundingSphere.h>
#include <Public\Line3D.h>


BEGIN_NAMESPACE


BoundingSphere::BoundingSphere(void)
{
	Reset();
}

	
void BoundingSphere::Reset(void)
{
	m_Radius = 0.0F;
}


void BoundingSphere::InsertPoint(const Vector3 &Point)
{
	const float len = Point.Length();

	if (len > m_Radius)
		m_Radius = len;
}


bool BoundingSphere::IntersectsWithLine(const Line3D &Line) const
{
	return true;
}


END_NAMESPACE
