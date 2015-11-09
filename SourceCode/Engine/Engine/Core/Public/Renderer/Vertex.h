// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VERTEX_H
#define VERTEX_H

#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Colour.h>

BEGIN_NAMESPACE

enum class VertexDeclarations
{
	Standard = 0,
	TwoTexCoords
};

class Vertex
{
public:
	INLINE Vertex(void) :
		Colour(Colour::WHITE)
	{
	}

	INLINE Vertex(float32 PositionX, float32 PositionY, float32 PositionZ,
		float32 NormalX, float32 NormalY, float32 NormalZ,
		float32 TexCoordU, float32 TexCoordV,
		uchar ColourRed, uchar ColourGreen, uchar ColourBlue, uchar ColourAlpha = 255) :
		Position(PositionX, PositionY, PositionZ),
		Normal(NormalX, NormalY, NormalZ),
		TexCoord(TexCoordU, TexCoordV),
		Colour(ColourRed, ColourGreen, ColourBlue, ColourAlpha)
	{
	}

	INLINE Vertex(const Vector3 &Position, const Vector3 &Normal, const Vector2 &TexCoord, const Colour &Colour = Colour::WHITE) :
		Position(Position),
		Normal(Normal),
		TexCoord(TexCoord),
		Colour(Colour)
	{
	}

public:
	Vector3 Position;
	Vector3 Normal;
	Colour Colour;
	Vector2 TexCoord;
};

class Vertex2Coords : public Vertex
{
	INLINE Vertex2Coords(float32 PositionX, float32 PositionY, float32 PositionZ,
		float32 NormalX, float32 NormalY, float32 NormalZ,
		float32 TexCoordU, float32 TexCoordV,
		float32 TexCoord2U, float32 TexCoord2V,
		uchar ColourRed, uchar ColourGreen, uchar ColourBlue, uchar ColourAlpha = 255) :
		Vertex(PositionX, PositionY, PositionZ, NormalX, NormalY, NormalZ, TexCoordU, TexCoordV, ColourRed, ColourGreen, ColourBlue, ColourAlpha),
		TexCoord2(TexCoord2U, TexCoord2V)
	{
	}

	INLINE Vertex2Coords(const Vector3 &Position, const Vector3 &Normal, const Vector2 &TexCoord, const Vector2 &TexCoord2, const NAMESPACE::Colour &Colour = Colour::WHITE) :
		Vertex(Position, Normal, TexCoord, Colour),
		TexCoord2(TexCoord2)
	{
	}

public:
	Vector2 TexCoord2;
};


END_NAMESPACE
#endif // VERTEX_H
