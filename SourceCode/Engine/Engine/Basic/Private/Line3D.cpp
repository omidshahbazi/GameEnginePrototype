// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Line3D.h>


BEGIN_NAMESPACE



Line3D::Line3D(void) :
	m_Start(Vector3::ZERO),
	m_End(Vector3::ZERO)
{
}


Line3D::Line3D(const Vector3 &Start, const Vector3 &End) :
	m_Start(Start),
	m_End(End)
{

}

Line3D::~Line3D(void)
{
}


END_NAMESPACE
