// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MESHRESOURCESMANAGERAPI_H
#define MESHRESOURCESMANAGERAPI_H
#include <Public\Utilities.h>
#include <Public\MeshResourcesManager.h>

BEGIN_NAMESPACE

API_FUNCTION MeshResourcesManager *MeshResourcesManager_GetPointer(void);

API_FUNCTION IMesh *MeshResourcesManager_GetBasicShapeMesh(IMesh::BasicShapes Shape);
API_FUNCTION IMesh *MeshResourcesManager_GetMesh(BSTR Name);
API_FUNCTION IMesh *MeshResourcesManager_CreateMesh(BSTR Name, uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignmentsIndexType, IMesh::PrimitiveType PrimitiveType);

END_NAMESPACE
#endif // MESHRESOURCESMANAGERAPI_H
