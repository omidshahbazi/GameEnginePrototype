// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Renderer : Component
	{
		public Material Material
		{
			get
			{
				IntPtr pointer = Renderer_GetMaterial(Pointer);

					return WrapperObject.GetObject<Material>(pointer);
			}
			set { Renderer_SetMaterial(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
		}

		public Mesh Mesh
		{
			get { return WrapperObject.GetObject<Mesh>(Renderer_GetMesh(Pointer)); }
			set { Renderer_SetMesh(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
		}

		public BoundingBox OrientedBoundinBox
		{
			get { return Renderer_GetOrientedBoundinBox(Pointer); }
		}

		public Renderer(IntPtr Pointer) :
			base(Pointer)
		{
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Renderer_SetMaterial(IntPtr Renderer, IntPtr Material);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Renderer_GetMaterial(IntPtr Renderer);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Renderer_SetMesh(IntPtr Renderer, IntPtr Mesh);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Renderer_GetMesh(IntPtr Renderer);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern BoundingBox Renderer_GetOrientedBoundinBox(IntPtr Renderer);
	}
}
