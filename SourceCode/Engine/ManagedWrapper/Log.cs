// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace ManagedWrapper
{
	public class Log
	{
		public delegate void Callback([MarshalAs(UnmanagedType.LPStr)] string Text, int Type);

		public static void SetCallback(Callback Callback)
		{
			Log_SetCallback(Callback);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Log_SetCallback(Callback Callback);
	}
}
