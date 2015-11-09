// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class RenderTarget : Texture
    {
        public Camera Camera
        {
            get { return WrapperObject.GetObject<Camera>(RenderTarget_GetCamera(Pointer)); }
            set { RenderTarget_SetCamera(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
        }

        public RenderTarget(IntPtr Pointer) :
			base(Pointer)
		{
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr RenderTarget_GetCamera(IntPtr RenderTarget);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void RenderTarget_SetCamera(IntPtr RenderTarget, IntPtr Camera);
	}
}
