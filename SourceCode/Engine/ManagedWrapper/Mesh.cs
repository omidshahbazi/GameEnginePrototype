// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;

namespace ManagedWrapper
{
	public class Mesh : WrapperObject
	{
		public enum IndexType
		{
			Bit_16 = 0,
			Bit_32
		};

		public enum PrimitiveType
		{
			Points = 0,
			LineStrip,
			LineLoop,
			Lines,
			TraingleStrip,
			TriangleFan,
			Triangles,
			QuadStrip,
			Quads,
			Polygon,
			PointStrip
		};

		public enum BasicShapes
		{
			Quad = 0,
			Cube
		};

		public Mesh(IntPtr Pointer) :
			base(Pointer)
		{
		}
    }
}
