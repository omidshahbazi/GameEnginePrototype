// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Material : WrapperObject
	{
		public uint PassesCount
		{
			get { return Material_GetPassesCount(Pointer); }
		}

		public Pass this[uint Index]
		{
			get { return GetPass(Index); }
		}

		public Material(IntPtr Pointer) :
			base(Pointer)
		{
		}

		public Pass CreatePass()
		{
			return new Pass(Material_CreatePass(Pointer));
		}

		public Pass GetPass(uint Index)
		{
			return WrapperObject.GetObject<Pass>(Material_GetPass(Pointer, Index));
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Material_CreatePass(IntPtr Material);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern uint Material_GetPassesCount(IntPtr Material);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Material_GetPass(IntPtr Material, uint Index);
	}
}
