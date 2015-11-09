// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[DebuggerDisplay("{r}, {g}, {b}, {a}")]
	[StructLayout(LayoutKind.Explicit, Size = 16)]
	public struct Colour
	{
		public enum Format
		{
			A1R5G5B5 = 0,
			R5G6B5,
			R8G8B8,
			A8R8G8B8,
			R16F,
			G16R16F,
			A16B16G16R16F,
			R32F,
			G32R32F,
			A32B32G32R32F
		};

		public static readonly Colour Black = new Colour(0, 0, 0, 255);
		public static readonly Colour White = new Colour(255, 255, 255, 255);
		public static readonly Colour Red = new Colour(255, 0, 0, 255);
		public static readonly Colour Green = new Colour(0, 255, 0, 255);
		public static readonly Colour Blue = new Colour(0, 0, 255, 255);
		public static readonly Colour Cyan = new Colour(0, 255, 255, 255);
		public static readonly Colour Yellow = new Colour(255, 255, 0, 255);
		public static readonly Colour Magenta = new Colour(255, 0, 255, 255);

		[FieldOffsetAttribute(3)]
		private byte a;
		[FieldOffsetAttribute(2)]
		private byte r;
		[FieldOffsetAttribute(1)]
		private byte g;
		[FieldOffsetAttribute(0)]
		private byte b;

		public byte A
		{
			get { return a; }
			set { a = value; }
		}

		public byte R
		{
			get { return r; }
			set { r = value; }
		}

		public byte G
		{
			get { return g; }
			set { g = value; }
		}

		public byte B
		{
			get { return b; }
			set { b = value; }
		}

		public Colour(byte R, byte G, byte B, byte A = 255)
		{
			b = B;
			g = G;
			r = R;
			a = A;
		}
	}
}
