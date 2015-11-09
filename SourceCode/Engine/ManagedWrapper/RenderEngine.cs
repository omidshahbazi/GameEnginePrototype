// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class RenderEngine : WrapperObject
	{
		public RenderEngine(IntPtr Pointer) :
			base(Pointer)
		{
		}

		public RenderWindow CreateRenderWindow(IntPtr WindowHandle)
		{
			return new RenderWindow(RenderEngine_CreateRenderWindow(Pointer, WindowHandle));
		}

		public void DestroyRenderWindow(RenderWindow Window)
		{
			RenderEngine_DestroyRenderWindow(Pointer, Window.Pointer);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr RenderEngine_CreateRenderWindow(IntPtr Core, IntPtr WindowHandle);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void RenderEngine_DestroyRenderWindow(IntPtr Core, IntPtr RenderWindow);
	}
}
