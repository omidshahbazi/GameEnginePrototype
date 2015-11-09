// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\BoundingBox.h>
#include <Public\Line3D.h>


BEGIN_NAMESPACE


BoundingBox::BoundingBox(void)
{
	Reset();
}

	
void BoundingBox::Reset(void)
{
	m_LowerCorner = m_UpperCorner = Vector3::ZERO;
}


void BoundingBox::InsertPoint(const Vector3 &Point)
{
	//if (m_IsZero)
	//{
	//	m_IsZero = false;

	//	m_Minimum = m_Maximum = Point;
	//}

	if (Point.X < m_LowerCorner.X)
		m_LowerCorner.X = Point.X;

	if (Point.Y < m_LowerCorner.Y)
		m_LowerCorner.Y = Point.Y;

	if (Point.Z < m_LowerCorner.Z)
		m_LowerCorner.Z = Point.Z;

	if (Point.X > m_UpperCorner.X)
		m_UpperCorner.X = Point.X;

	if (Point.Y > m_UpperCorner.Y)
		m_UpperCorner.Y = Point.Y;

	if (Point.Z > m_UpperCorner.Z)
		m_UpperCorner.Z = Point.Z;
}


float32 BoundingBox::GetInnerRadius(void) const
{
	const Vector3 half = (m_UpperCorner - m_LowerCorner) / 2.f;

	return (half.X < half.Y ? half.X : half.Y);
}


float32 BoundingBox::GetOuterRadius(void) const
{
	return ((m_UpperCorner - m_LowerCorner) / 2.f).Length();
}


bool BoundingBox::IntersectsWithLine(const Line3D &Line) const
{
	//Vector3 normalPlane = (m_Corners[1] - m_Corners[0]).CrossProduct((m_Corners[2] - m_Corners[0])).Normalized();
	//float32 t = (-(Line.GetStart().DotProduct(normalPlane))) / (Line.GetDirection().Normalized().DotProduct(normalPlane));

	//Vector3 point = Line.GetStart() + Line.GetDirection().Normalized() * t;

	//const Vector3 v1 = m_Corners[0] - Line.GetStart();
	//const Vector3 v2 = m_Corners[1] - Line.GetStart();
	//const Vector3 n = v2.CrossProduct(v1).Normalized();

	//float32 d = Line.GetStart().DotProduct(n);

	//float32 f = point.DotProduct(n);

	//if ((point.DotProduct(n) * d) < 0)
	//	return false;
	//else
		return true;
}


END_NAMESPACE
