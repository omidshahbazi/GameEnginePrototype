// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[DebuggerDisplay("{x}, {y}, {z}")]
	[StructLayout(LayoutKind.Explicit)]
	public struct Vector3
    {
        public static readonly Vector3 Zero = new Vector3(0, 0, 0);
        public static readonly Vector3 One = new Vector3(1, 1, 1);
        public static readonly Vector3 UnitX = new Vector3(1, 0, 0);
        public static readonly Vector3 UnitY = new Vector3(0, 1, 0);
        public static readonly Vector3 UnitZ = new Vector3(0, 0, 1);

		[FieldOffsetAttribute(0)]
		private float x;
		[FieldOffsetAttribute(4)]
		private float y;
		[FieldOffsetAttribute(8)]
		private float z;

		public float X
		{
			get { return x; }
			set { x = value; }
		}

		public float Y
		{
			get { return y; }
			set { y = value; }
		}

		public float Z
		{
			get { return z; }
			set { z = value; }
		}

		public Vector3(float X, float Y, float Z)
		{
			x = X;
			y = Y;
			z = Z;
		}
	}
}
