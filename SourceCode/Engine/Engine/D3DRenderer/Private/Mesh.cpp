// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Mesh.h>
#include <Public\Core.h>
#include <Private\RenderEngine.h>
#include <Private\RendererCommon.h>

BEGIN_NAMESPACE


void Mesh::SetVertices(const Vertex *Vertices)
{
	void *buffer;
	m_VertexBuffer->Lock(0, 0, &buffer, 0);
	memcpy(buffer, Vertices, m_VerticesBytesLen);
	m_VertexBuffer->Unlock();

	m_BoundingSphere.Reset();
	for (uint32 i = 0; i < m_VerticesCount; i++)
		m_BoundingSphere.InsertPoint(Vertices[i].Position);
}


void Mesh::SetIndices(const void *Indices)
{
	void *buffer;
	m_IndexBuffer->Lock(0, 0, &buffer, 0);
	memcpy(buffer, Indices, m_IndicesBytesLen);
	m_IndexBuffer->Unlock();
}


void Mesh::CreateBuffers(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 PrimitivesCount, PrimitiveTypes PrimitiveType)
{
	static IDirect3DDevice9 *device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	m_VerticesCount = VerticesCount;
	m_VertexDeclaration = VertexDeclaration;
	m_PrimitivesCount = PrimitivesCount;
	m_PrimitiveType = PrimitiveType;

	m_VertexStride = GET_FVF_STRIDE(m_VertexDeclaration);

	m_VerticesBytesLen = m_VertexStride * m_VerticesCount;

	device->CreateVertexBuffer(m_VerticesBytesLen, D3DUSAGE_WRITEONLY, TO_FVF(VertexDeclaration), D3DPOOL_MANAGED, &m_VertexBuffer, NULL);
}


void Mesh::CreateBuffers(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment, PrimitiveTypes PrimitiveType)
{
	static IDirect3DDevice9 *device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	CreateBuffers(VerticesCount, VertexDeclaration, IndicesCount / 3, PrimitiveType);

	m_IndexDataAlignment = IndexDataAlignment;

	m_IndexStride = GET_INDEX_STRIDE(m_IndexDataAlignment);

	m_IndicesBytesLen = m_IndexStride * IndicesCount;

	device->CreateIndexBuffer(m_IndicesBytesLen, D3DUSAGE_WRITEONLY, TO_FMT(IndexDataAlignment), D3DPOOL_MANAGED, &m_IndexBuffer, NULL);
}


END_NAMESPACE
