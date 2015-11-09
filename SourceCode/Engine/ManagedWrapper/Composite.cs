// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Composite : WrapperObject
	{
		public uint PassesCount
		{
            get { return Composite_GetPassesCount(Pointer); }
		}

        public CompositePass this[uint Index]
		{
			get { return GetPass(Index); }
		}

        public Composite(IntPtr Pointer) :
			base(Pointer)
		{
		}

        public CompositePass CreatePass()
		{
            return new CompositePass(Composite_CreatePass(Pointer));
		}

        public CompositePass GetPass(uint Index)
		{
            return WrapperObject.GetObject<CompositePass>(Composite_GetPass(Pointer, Index));
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Composite_CreatePass(IntPtr Composite);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Composite_GetPassesCount(IntPtr Composite);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Composite_GetPass(IntPtr Composite, uint Index);
	}
}
