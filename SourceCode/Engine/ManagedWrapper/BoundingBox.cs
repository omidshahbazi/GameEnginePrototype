// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[DebuggerDisplay("{LowerCorner}, {UpperCorner}")]
	[StructLayout(LayoutKind.Explicit)]
	public struct BoundingBox
	{
		[FieldOffsetAttribute(0)]
		Vector3 LowerCorner;
		[FieldOffsetAttribute(12)]
		Vector3 UpperCorner;
	}
}
