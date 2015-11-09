// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Component : WrapperObject
	{
		public bool Enabled
		{
			get { return Component_GetEnabled(Pointer); }
			set { Component_SetEnabled(Pointer, value); }
		}

		public GameObject Holder
		{
			get { return WrapperObject.GetObject<GameObject>(Component_GetHolder(Pointer)); }
		}

		public Component(IntPtr Pointer) :
			base(Pointer)
		{
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		private static extern bool Component_GetEnabled(IntPtr Component);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Component_SetEnabled(IntPtr Component, bool Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Component_GetHolder(IntPtr Component);
	}
}
