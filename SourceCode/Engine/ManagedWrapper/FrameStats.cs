// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	[DebuggerDisplay("{fPS}, {averageFrameTime}")]
	[StructLayout(LayoutKind.Explicit, Size = 24)]
	public struct FrameStats
	{
		[FieldOffsetAttribute(0)]
        private int targetFPS;
		[FieldOffsetAttribute(2)]
		private float targetFrameTime;
		[FieldOffsetAttribute(6)]
		private int fPS;
		[FieldOffsetAttribute(8)]
		private float averageFrameTime;

        public int TargetFPS
		{
			get { return targetFPS; }
		}

		public float TargetFrameTime
		{
			get { return targetFrameTime; }
		}

        public int FPS
		{
			get { return fPS; }
		}

		public float AverageFrameTime
		{
			get { return averageFrameTime; }
		}
	}
}
