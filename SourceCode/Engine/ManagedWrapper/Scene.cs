// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Scene : WrapperObject
	{
		public string Name
		{
			get { return Scene_GetName(Pointer); }
		}

		public bool Active
		{
			get { return Scene_GetActive(Pointer); }
			set { Scene_SetActive(Pointer, value); }
		}

		public Scene(IntPtr Pointer, string Name) :
			base(Pointer)
		{
		}

		public void Clear()
		{
			Scene_Clear(Pointer);
		}

		public GameObject CreateGameObject(string Name)
		{
			return CreateGameObject(Name, (Transform)null);
		}

		public GameObject CreateGameObject(string Name, GameObject Parent)
		{
			return CreateGameObject(Name, (Parent == null ? null : Parent.Transform));
		}

		public GameObject CreateGameObject(string Name, Transform Parent)
		{
			return new GameObject(Scene_CreateGameObject(Pointer, Name, (Parent == null ? IntPtr.Zero : Parent.Pointer)), Name);
		}

		public void DestroyGameObject(GameObject GameObject)
		{
			if (GameObject == null)
				return;

			Scene_DestroyGameObject(Pointer, GameObject.Pointer);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.BStr)]
		private static extern void Scene_Clear(IntPtr Scene);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern string Scene_GetName(IntPtr Scene);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Scene_CreateGameObject(IntPtr Scene, [MarshalAs(UnmanagedType.BStr)] string Name, IntPtr ParentTransform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Scene_DestroyGameObject(IntPtr Scene, IntPtr GameObject);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Scene_SetActive(IntPtr Scene, bool Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		private static extern bool Scene_GetActive(IntPtr Scene);
	}
}
