// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class MeshResourcesManager : ResourcesManager<MeshResourcesManager>
	{
		private static readonly MeshResourcesManager instance = new MeshResourcesManager();

		public static MeshResourcesManager Instance
		{
			get { return instance; }
		}

		private MeshResourcesManager() :
			base(MeshResourcesManager_GetPointer())
		{
		}

		public Mesh GetMesh(Mesh.BasicShapes Shape)
		{
			return WrapperObject.GetObject<Mesh>(MeshResourcesManager_GetBasicShapeMesh(Shape));
		}

		public Mesh GetMesh(string Name)
		{
			return WrapperObject.GetObject<Mesh>(MeshResourcesManager_GetMesh(Name));
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MeshResourcesManager_GetPointer();

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MeshResourcesManager_GetBasicShapeMesh(Mesh.BasicShapes Shape);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MeshResourcesManager_GetMesh([MarshalAs(UnmanagedType.BStr)] string Name);

		//IntPtr MeshResourcesManager_CreateMesh(const String &Name, uint32 VerticesCount, VertexDeclarations VertexDeclaration, uint32 IndicesCount, IndexDataAlignmentsIndexType, IMesh::PrimitiveType PrimitiveType)
	}
}
