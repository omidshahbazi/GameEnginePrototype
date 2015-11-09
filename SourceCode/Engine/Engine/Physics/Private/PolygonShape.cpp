// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\PolygonShape.h>
#include <Private\PhysicsCommon.h>


BEGIN_NAMESPACE


PolygonShape::PolygonShape(b2PolygonShape *Shape) :
	m_Shape(Shape)

{
	m_Type = ST_POLYGON;

	for (int i = 0; i < m_Shape->GetVertexCount(); i++)
		m_Vertices.Add(ToVector2(m_Shape->GetVertex(i)));

	m_VertexCount = m_Vertices.GetSize();

	m_Center = ToVector2(m_Shape->m_centroid);
}


END_NAMESPACE

