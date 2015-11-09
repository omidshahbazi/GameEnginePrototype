// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class MaterialResourcesManager : ResourcesManager<MaterialResourcesManager>
	{
		private static readonly MaterialResourcesManager instance = new MaterialResourcesManager();

		public static MaterialResourcesManager Instance
		{
			get { return instance; }
		}

		private MaterialResourcesManager() :
			base(MaterialResourcesManager_GetPointer())
		{
		}

		public Material GetMaterial(string Name)
		{
			return WrapperObject.GetObject<Material>(MaterialResourcesManager_GetMaterial(Name));
		}

		public Material CreateMaterial(string Name)
		{
			return WrapperObject.GetObject<Material>(MaterialResourcesManager_CreateMaterial(Name));
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MaterialResourcesManager_GetPointer();

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MaterialResourcesManager_GetMaterial([MarshalAs(UnmanagedType.BStr)] string Name);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr MaterialResourcesManager_CreateMaterial([MarshalAs(UnmanagedType.BStr)] string Name);
	}
}
