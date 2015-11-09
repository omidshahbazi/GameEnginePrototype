// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Texture : WrapperObject
	{
		public Vector2 Size
		{
			get { return Texture_GetSize(Pointer); }
		}

		public Texture(IntPtr Pointer) :
			base(Pointer)
		{
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector2 Texture_GetSize(IntPtr Texture);
	}
}
