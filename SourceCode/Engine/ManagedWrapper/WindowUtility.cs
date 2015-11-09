// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class WindowUtility
	{
		public static void WndProc(IntPtr Handle, int Message, int wParam, int lParam)
		{
			WindowUtility_WndProc(Handle, Message, wParam, lParam);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void WindowUtility_WndProc(IntPtr Handle, int Message, int wParam, int lParam);
	}
}
