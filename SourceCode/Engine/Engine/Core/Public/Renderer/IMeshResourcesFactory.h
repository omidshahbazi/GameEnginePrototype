// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMESHRESOURCESFACTORY_H
#define IMESHRESOURCESFACTORY_H

#include <Public\IResourcesFactory.h>
#include <Public\Renderer\IMesh.h>

BEGIN_NAMESPACE

class IMeshResourcesFactory : public IResourcesFactory
{
public:
	virtual ~IMeshResourcesFactory(void) {}

	virtual IMesh *GetBasicShapeMesh(BasicShapes Shape) const = 0;
	virtual IMesh *CreateMesh(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignments, PrimitiveTypes PrimitiveType) const = 0;
};

END_NAMESPACE
#endif // IMESHRESOURCESFACTORY_H
