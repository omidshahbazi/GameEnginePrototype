// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	class ResourcesManagerNativeMethods
	{
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		public static extern void ResourcesManager_Reimport(IntPtr ResourcesManager);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		public static extern bool ResourcesManager_HasResource(IntPtr ResourcesManager, [MarshalAs(UnmanagedType.BStr)] string Name);
	}

	public class ResourcesManager<T> : WrapperObject
	{
		public ResourcesManager(IntPtr Pointer) :
			base(Pointer)
		{
		}

		public void Reimport()
		{
			ResourcesManagerNativeMethods.ResourcesManager_Reimport(Pointer);
		}

		public bool HasResource(string Name)
		{
			return ResourcesManagerNativeMethods.ResourcesManager_HasResource(Pointer, Name);
		}
	}
}
