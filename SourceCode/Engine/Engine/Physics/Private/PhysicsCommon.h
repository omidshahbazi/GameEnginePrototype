// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PHYSICSCOMMON_H
#define PHYSICSCOMMON_H

#include "Vector2.h"
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

inline b2Vec2 Tob2Vec2(const Vector2 &Vector)
{
	return b2Vec2(Vector.X, Vector.Y);
}

inline Vector2 ToVector2(const b2Vec2 &Vector)
{
	Vector2 vector;
	vector.X = Vector.x;
	vector.Y = Vector.y;
	return vector;
}

inline b2Vec2 *Tob2Vec2(const List<Vector2> &Vertices)
{
	const unsigned &vertexCount = Vertices.GetSize();

	b2Vec2 *NewVertices = new b2Vec2[vertexCount];

	for (unsigned int i = 0; i < vertexCount; i++)
		NewVertices[i] = Tob2Vec2(Vertices[i]);

	return NewVertices;
}

inline Vector2 *ToVector2(const b2Vec2 *Vertices, int32 VertexCount)
{
	Vector2 *NewVertices = new Vector2[VertexCount];

	for (int i = 0; i < VertexCount; i++)
	{
		NewVertices[i] = ToVector2(Vertices[i]);
	}

	return NewVertices;
}


END_NAMESPACE
#endif // PHYSICSCOMMON_H
