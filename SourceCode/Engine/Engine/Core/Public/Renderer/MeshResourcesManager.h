// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MESHRESOURCESMANAGER_H
#define MESHRESOURCESMANAGER_H

#include <Public\Singleton.h>
#include <Public\ResourcesManager.h>
#include <Public\Renderer\IMeshResourcesFactory.h>

BEGIN_NAMESPACE

class CORE_API MeshResourcesManager : ResourcesManager
{
	DECLARE_SINGLETON(MeshResourcesManager)

private:
	MeshResourcesManager(void) {}

public:
	INLINE IMesh *GetMesh(BasicShapes Shape)
	{
		return m_Factory->GetBasicShapeMesh(Shape);
	}
	INLINE IMesh *GetMesh(const String &Name)
	{
		return (IMesh*)GetOrLoadResource(Name);
	}
	INLINE IMesh *CreateMesh(const String &Name, uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment, PrimitiveTypes PrimitiveType = PrimitiveTypes::Triangles)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a Mesh named [" + Name + "]")

				return NULL;
		}

		IMesh *mesh = m_Factory->CreateMesh(VerticesCount, VertexDeclaration, IndicesCount, IndexDataAlignment, PrimitiveType);
		if (mesh)
			AddResource(Name, mesh);
		return mesh;
	}

	INLINE void Initialize(IMeshResourcesFactory *Factory)
	{
		m_Factory = Factory;

		Reimport();
	}

private:
	INLINE IResourcesFactory *GetFactory(void) const
	{
		return m_Factory;
	}

private:
	IMeshResourcesFactory *m_Factory;
};

END_NAMESPACE
#endif // MESHRESOURCESMANAGER_H
