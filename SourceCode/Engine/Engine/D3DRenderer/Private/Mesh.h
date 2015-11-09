// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MESH_H
#define MESH_H
#include <Public\Renderer\IMesh.h>
#include <Public\BoundingSphere.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class Mesh : public IMesh
{
public:
	Mesh(void) :
		m_VertexBuffer(NULL),
		m_IndexBuffer(NULL)
	{
	}
	Mesh(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment, PrimitiveTypes PrimitiveType) :
		m_VertexBuffer(NULL),
		m_IndexBuffer(NULL)
	{
		CreateBuffers(VerticesCount, VertexDeclaration, IndicesCount, IndexDataAlignment, PrimitiveType);
	}
	Mesh(const Vertex *Vertices, uint32 VerticesCount, VertexDeclarations VertexDeclaration, const void *Indices, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment) :
		m_VertexBuffer(NULL),
		m_IndexBuffer(NULL)
	{
		CreateBuffers(VerticesCount, VertexDeclaration, IndicesCount, IndexDataAlignment, PrimitiveTypes::Triangles);

		SetVertices(Vertices);
		SetIndices(Indices);
	}

	virtual ~Mesh(void)
	{
		m_VertexBuffer->Release();

		if (m_IndexBuffer)
			m_IndexBuffer->Release();
	}

	void SetVertices(const Vertex *Vertices);
	void SetIndices(const void *Indices);

	const BoundingSphere &GetBoundingSphere(void) const
	{
		return m_BoundingSphere;
	}

	void CreateBuffers(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 PrimitivesCount, PrimitiveTypes PrimitiveType);
	void CreateBuffers(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment, PrimitiveTypes PrimitiveType);

	IDirect3DVertexBuffer9 *GetVertexBuffer(void)
	{
		return m_VertexBuffer;
	}
	VertexDeclarations GetVertexDeclaration(void)
	{
		return m_VertexDeclaration;
	}
	uint32 GetVerticesCount(void)
	{
		return m_VerticesCount;
	}
	uint32 GetVertexStride(void)
	{
		return m_VertexStride;
	}
	IDirect3DIndexBuffer9 *GetIndexBuffer(void)
	{
		return m_IndexBuffer;
	}
	IndexDataAlignments GetIndexDataAlignment(void)
	{
		return m_IndexDataAlignment;
	}
	uint32 GetIndexStride(void)
	{
		return m_IndexStride;
	}
	uint32 GetPrimitivesCount(void)
	{
		return m_PrimitivesCount;
	}
	PrimitiveTypes GetPrimitiveType(void)
	{
		return m_PrimitiveType;
	}

private:
	IDirect3DVertexBuffer9 *m_VertexBuffer;
	VertexDeclarations m_VertexDeclaration;
	uint32 m_VerticesCount;
	uint32 m_VertexStride;
	IDirect3DIndexBuffer9 *m_IndexBuffer;
	IndexDataAlignments m_IndexDataAlignment;
	uint32 m_IndexStride;
	uint32 m_PrimitivesCount;
	PrimitiveTypes m_PrimitiveType;

	uint32 m_VerticesBytesLen;
	uint32 m_IndicesBytesLen;

	BoundingSphere m_BoundingSphere;
};

END_NAMESPACE
#endif // MESH_H
