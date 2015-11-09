// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[StructLayout(LayoutKind.Sequential, Size = 128)]
	public struct Matrix4
	{
		private float[] m_Cells;
	}
}
