// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Image : WrapperObject
	{
        public Image(IntPtr Pointer) :
			base(Pointer)
		{
		}
	}
}
