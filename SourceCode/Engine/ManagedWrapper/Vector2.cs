// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[DebuggerDisplay("{x}, {y}")]
	[StructLayout(LayoutKind.Explicit, Size = 16)]
	public struct Vector2
    {
        public static readonly Vector2 Zero = new Vector2(0, 0);
        public static readonly Vector2 One = new Vector2(1, 1);
        public static readonly Vector2 UnitX = new Vector2(1, 0);
        public static readonly Vector2 UnitY = new Vector2(0, 1);

		[FieldOffsetAttribute(0)]
		public float x;
		[FieldOffsetAttribute(4)]
		public float y;

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

		public Vector2(float X, float Y)
		{
			x = X;
			y = Y;
		}

        public static Vector2 operator *(Vector2 Left, float Right)
        {
            return new Vector2(Left.x * Right, Left.y * Right);
        }
	}
}
