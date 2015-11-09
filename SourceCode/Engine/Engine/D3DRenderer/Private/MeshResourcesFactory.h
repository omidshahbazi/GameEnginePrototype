// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MESHFACTORY_H
#define MESHFACTORY_H

#include <Public\Renderer\MeshResourcesManager.h>
#include <Private\MeshBasicShapes.h>
#include <Private\FBXInclude.h>

BEGIN_NAMESPACE

class MeshResourcesFactory : public IMeshResourcesFactory
{
public:
	MeshResourcesFactory(void) :
		m_FBXManager(FbxManager::Create())
	{
		m_FBXManager->SetIOSettings(FbxIOSettings::Create(m_FBXManager, Core::GetReference().GetDataPath().GetBuffer()));
	}

private:
	Resource *LoadResource(const String &Name) const
	{
		static const String &dataPath = Core::GetReference().GetDataPath();

		FbxImporter *importer = FbxImporter::Create(m_FBXManager, "");
		importer->Initialize((dataPath + Name).GetBuffer(), -1, m_FBXManager->GetIOSettings());
		FbxScene *scene = FbxScene::Create(m_FBXManager, "t");
		importer->Import(scene);

		Mesh *mesh = NULL;

		FbxNode* node = scene->GetRootNode();
		if (node)
		{
			for (int i = 0; i < node->GetChildCount(); i++)
			{
				FbxMesh* fbxMesh = node->GetChild(i)->GetMesh();

				if (fbxMesh)
				{
					const int verticesCount = fbxMesh->GetControlPointsCount();

					Vertex *vertices = new Vertex[verticesCount];

					FbxVector4 *verticesFbx = fbxMesh->GetControlPoints();

					FbxArray<FbxVector4> normals;
					fbxMesh->GetPolygonVertexNormals(normals);

					FbxLayerElementArrayTemplate<FbxVector2> *uv = NULL;
					fbxMesh->GetTextureUV(&uv);

					for (int v = 0; v < verticesCount; v++)
					{
						vertices[v].Position.X = (float)verticesFbx[v][0];
						vertices[v].Position.Y = (float)verticesFbx[v][1];
						vertices[v].Position.Z = (float)verticesFbx[v][2];

						vertices[v].Normal.X = (float)normals[v][0];
						vertices[v].Normal.Y = (float)normals[v][1];
						vertices[v].Normal.Z = (float)normals[v][2];

						vertices[v].Normal.X = (float)normals[v][0];
						vertices[v].Normal.Y = (float)normals[v][1];
						vertices[v].Normal.Z = (float)normals[v][2];

						vertices[v].TexCoord.X = (float)uv->operator[](v)[0];
						vertices[v].TexCoord.Y = (float)uv->operator[](v)[1];
					}

					mesh = new Mesh(vertices, verticesCount, VertexDeclarations::Standard, fbxMesh->GetPolygonVertices(), fbxMesh->GetPolygonVertexCount(), IndexDataAlignments::Bit32);

					delete []vertices;
				}
			}
		}

		scene->Destroy(true);
		importer->Destroy(true);

		return mesh;
	}

	IMesh *GetBasicShapeMesh(BasicShapes Shape) const
	{
		static QuadMesh QUAD_MESH;
		static CubeMesh CUBE_MESH;

		switch (Shape)
		{
		case BasicShapes::Quad:
			return &QUAD_MESH;
			break;
		case BasicShapes::Cube:
			return &CUBE_MESH;
			break;
		}

		return NULL;
	}

	IMesh *CreateMesh(uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignments IndexDataAlignment, PrimitiveTypes PrimitiveType = PrimitiveTypes::Triangles) const
	{
		return new Mesh(VerticesCount, VertexDeclaration, IndicesCount, IndexDataAlignment, PrimitiveType);
	}

	const String &GetSupportedExtensions(void) const
	{
		static const String Supported_Extensions("fbx");

		return Supported_Extensions;
	}

	bool IsExtensionSupported(const String &Extension) const
	{
		static const String Supported_Extensions("fbx");

		return Supported_Extensions == Extension.ToLowerCase();
	}

private:
	FbxManager *m_FBXManager;
};

END_NAMESPACE
#endif // MESHFACTORY_H
