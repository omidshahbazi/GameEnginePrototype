// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\MeshResourcesManagerAPI.h>

BEGIN_NAMESPACE

MeshResourcesManager *MeshResourcesManager_GetPointer(void)
{
	return MeshResourcesManager::GetPointer();
}


IMesh *MeshResourcesManager_GetBasicShapeMesh(IMesh::BasicShapes Shape)
{
	return MeshResourcesManager::GetReference().GetMesh(Shape);
}


IMesh *MeshResourcesManager_GetMesh(BSTR Name)
{
	return MeshResourcesManager::GetReference().GetMesh(TO_String(Name));
}


IMesh *MeshResourcesManager_CreateMesh(BSTR Name, uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignmentsIndexType, IMesh::PrimitiveType PrimitiveType)
{
	return MeshResourcesManager::GetReference().CreateMesh(TO_String(Name), VerticesCount, VertexDeclaration, IndicesCount, IndexType, PrimitiveType);
}


END_NAMESPACE
