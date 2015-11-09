// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class RenderWindow : WrapperObject
	{
		public Camera Camera
		{
			get { return WrapperObject.GetObject<Camera>(RenderWindow_GetCamera(Pointer)); }
			set { RenderWindow_SetCamera(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
		}

		public RenderWindow(IntPtr Pointer) :
			base(Pointer)
		{
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr RenderWindow_GetCamera(IntPtr RenderWindow);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void RenderWindow_SetCamera(IntPtr RenderWindow, IntPtr Camera);
	}
}
