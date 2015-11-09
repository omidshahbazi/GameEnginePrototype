// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class CompositeResourcesManager : ResourcesManager<CompositeResourcesManager>
	{
		private static readonly CompositeResourcesManager instance = new CompositeResourcesManager();

		public static CompositeResourcesManager Instance
		{
			get { return instance; }
		}

		private CompositeResourcesManager() :
			base(CompositeResourcesManager_GetPointer())
		{
		}

        public Composite GetComposite(string Name)
		{
            return WrapperObject.GetObject<Composite>(CompositeResourcesManager_GetComposite(Name));
		}

        public Composite CreateComposite(string Name)
		{
            return WrapperObject.GetObject<Composite>(CompositeResourcesManager_CreateComposite(Name));
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr CompositeResourcesManager_GetPointer();

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr CompositeResourcesManager_GetComposite([MarshalAs(UnmanagedType.BStr)] string Name);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr CompositeResourcesManager_CreateComposite([MarshalAs(UnmanagedType.BStr)] string Name);
	}
}
