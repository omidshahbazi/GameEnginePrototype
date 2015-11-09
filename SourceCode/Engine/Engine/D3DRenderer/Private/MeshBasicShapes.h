// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MESHBASICSHAPES_H
#define MESHBASICSHAPES_H

#include <Private\Mesh.h>

BEGIN_NAMESPACE

const float32 HALF_UNIT = 0.5F;

class QuadMesh : public Mesh
{
public:
	QuadMesh(void)
	{
		CreateBuffers(4, VertexDeclarations::Standard, 6, IndexDataAlignments::Bit16, PrimitiveTypes::Triangles);

		Vertex vertices[4];
		vertices[0].Position.X = -HALF_UNIT; vertices[0].Position.Y = -HALF_UNIT;
		vertices[1].Position.X = -HALF_UNIT; vertices[1].Position.Y = HALF_UNIT;
		vertices[2].Position.X = HALF_UNIT; vertices[2].Position.Y = HALF_UNIT;
		vertices[3].Position.X = HALF_UNIT; vertices[3].Position.Y = -HALF_UNIT;

		vertices[0].Normal =
			vertices[1].Normal =
			vertices[2].Normal =
			vertices[3].Normal = Vector3::UNIT_Z * -1;
		//vertices[0].Normal.X = 0.333333F; vertices[0].Normal.Y = 0.666667F; vertices[0].Normal.Z = -0.666667F;
		//vertices[1].Normal.X = -0.816497F; vertices[1].Normal.Y = 0.408248F; vertices[1].Normal.Z = -0.408248F;
		//vertices[2].Normal.X = -0.333333F; vertices[2].Normal.Y = 0.666667F; vertices[2].Normal.Z = 0.666667F;
		//vertices[3].Normal.X = 0.816497F; vertices[3].Normal.Y = 0.408248F; vertices[3].Normal.Z = 0.408248F;

		//vertices[0].Colour = Colour::WHITE;
		//vertices[1].Colour = Colour::RED;
		//vertices[2].Colour = Colour::GREEN;
		//vertices[3].Colour = Colour::BLUE;

		vertices[0].TexCoord.X = 0; vertices[0].TexCoord.Y = 1;
		vertices[1].TexCoord.X = 0; vertices[1].TexCoord.Y = 0;
		vertices[2].TexCoord.X = 1; vertices[2].TexCoord.Y = 0;
		vertices[3].TexCoord.X = 1; vertices[3].TexCoord.Y = 1;
		SetVertices(vertices);

		const uint16 indices[] = { 
			1, 2, 0, 
			2, 3, 0 };

		SetIndices(indices);
	}
};

class CubeMesh : public Mesh
{
public:
	CubeMesh(void)
	{
		CreateBuffers(16, VertexDeclarations::Standard, 36, IndexDataAlignments::Bit16, PrimitiveTypes::Triangles);

		Vertex vertices[16];
		vertices[0].Position.X = -HALF_UNIT; vertices[0].Position.Y = -HALF_UNIT; vertices[0].Position.Z = HALF_UNIT;
		vertices[1].Position.X = HALF_UNIT; vertices[1].Position.Y = -HALF_UNIT; vertices[1].Position.Z = HALF_UNIT;
		vertices[2].Position.X = HALF_UNIT; vertices[2].Position.Y = HALF_UNIT; vertices[2].Position.Z = HALF_UNIT;
		vertices[3].Position.X = -HALF_UNIT; vertices[3].Position.Y = HALF_UNIT; vertices[3].Position.Z = HALF_UNIT;

		vertices[4].Position.X = -HALF_UNIT; vertices[4].Position.Y = HALF_UNIT; vertices[4].Position.Z = -HALF_UNIT;
		vertices[5].Position.X = HALF_UNIT; vertices[5].Position.Y = HALF_UNIT; vertices[5].Position.Z = -HALF_UNIT;
		vertices[6].Position.X = HALF_UNIT; vertices[6].Position.Y = -HALF_UNIT; vertices[6].Position.Z = -HALF_UNIT;
		vertices[7].Position.X = -HALF_UNIT; vertices[7].Position.Y = -HALF_UNIT; vertices[7].Position.Z = -HALF_UNIT;

		vertices[8].Position.X = HALF_UNIT; vertices[8].Position.Y = -HALF_UNIT; vertices[8].Position.Z = HALF_UNIT;
		vertices[9].Position.X = HALF_UNIT; vertices[9].Position.Y = -HALF_UNIT; vertices[9].Position.Z = -HALF_UNIT;
		vertices[10].Position.X = HALF_UNIT; vertices[10].Position.Y = HALF_UNIT; vertices[10].Position.Z = -HALF_UNIT;
		vertices[11].Position.X = HALF_UNIT; vertices[11].Position.Y = HALF_UNIT; vertices[11].Position.Z = HALF_UNIT;

		vertices[12].Position.X = -HALF_UNIT; vertices[12].Position.Y = HALF_UNIT; vertices[12].Position.Z = -HALF_UNIT;
		vertices[13].Position.X = -HALF_UNIT; vertices[13].Position.Y = -HALF_UNIT; vertices[13].Position.Z = HALF_UNIT;
		vertices[14].Position.X = -HALF_UNIT; vertices[14].Position.Y = HALF_UNIT; vertices[14].Position.Z = HALF_UNIT;
		vertices[15].Position.X = -HALF_UNIT; vertices[15].Position.Y = HALF_UNIT; vertices[15].Position.Z = -HALF_UNIT;

		vertices[0].TexCoord.X = 0; vertices[0].TexCoord.Y = 0;
		vertices[1].TexCoord.X = 1; vertices[1].TexCoord.Y = 0;
		vertices[2].TexCoord.X = 1; vertices[2].TexCoord.Y = 1;
		vertices[3].TexCoord.X = 0; vertices[3].TexCoord.Y = 1;

		vertices[4].TexCoord.X = 0; vertices[4].TexCoord.Y = 0;
		vertices[5].TexCoord.X = 1; vertices[5].TexCoord.Y = 0;
		vertices[6].TexCoord.X = 1; vertices[6].TexCoord.Y = 1;
		vertices[7].TexCoord.X = 0; vertices[7].TexCoord.Y = 1;

		vertices[8].TexCoord.X = 0; vertices[8].TexCoord.Y = 0;
		vertices[9].TexCoord.X = 1; vertices[9].TexCoord.Y = 0;
		vertices[10].TexCoord.X = 0; vertices[10].TexCoord.Y = 1;
		vertices[11].TexCoord.X = 0; vertices[11].TexCoord.Y = 1;

		vertices[12].TexCoord.X = 0; vertices[12].TexCoord.Y = 0;
		vertices[13].TexCoord.X = 1; vertices[13].TexCoord.Y = 0;
		vertices[14].TexCoord.X = 1; vertices[14].TexCoord.Y = 1;
		vertices[15].TexCoord.X = 0; vertices[15].TexCoord.Y = 1;

		vertices[0].Colour = Colour::BLACK;
		vertices[1].Colour = Colour::WHITE;
		vertices[2].Colour = Colour::RED;;
		vertices[3].Colour = Colour::GREEN;
		vertices[4].Colour = Colour::BLUE;
		vertices[5].Colour = Colour::CYAN;
		vertices[6].Colour = Colour::YELLOW;
		vertices[7].Colour = Colour::MAGENTA;
		vertices[8].Colour = Colour::BLUE;
		vertices[9].Colour = Colour::CYAN;
		vertices[10].Colour = Colour::YELLOW;
		vertices[11].Colour = Colour::MAGENTA;
		vertices[12].Colour = Colour::BLUE;
		vertices[13].Colour = Colour::CYAN;
		vertices[14].Colour = Colour::YELLOW;
		vertices[15].Colour = Colour::MAGENTA;
		
		SetVertices(vertices);

		const uint16 indices[] = {
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4,

			7, 6, 1,
			7, 1, 0,
		
			8, 9, 10,
			8, 10, 11,
		
			12, 13, 14,
			12, 14, 15 };

		//const uint16 indices[] = {
		//	0, 1, 2,
		//	1, 2, 3,

		//	4, 5, 6,
		//	5, 6, 7,

		//	3, 2, 5,
		//	2, 5, 4,

		//	7, 6, 1,
		//	6, 1, 0,

		//	8, 9, 10,
		//	9, 10, 11,

		//	12, 13, 14,
		//	13, 14, 15 };

		SetIndices(indices);
	}
};

END_NAMESPACE
#endif // MESHBASICSHAPES_H
