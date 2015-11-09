// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class GPUProgramUsage : WrapperObject
	{
		public GPUProgram Program
		{
			get { return WrapperObject.GetObject<GPUProgram>(GPUProgramUsage_GetProgram(Pointer)); }
		}

		public GPUProgramUsage(IntPtr Pointer) :
			base(Pointer)
		{
		}

		public void ClearAutoParams()
		{
			GPUProgramUsage_ClearAutoParams(Pointer);
		}

		public void SetAutoParam(string Constant, string Param)
		{
			GPUProgramUsage_SetAutoParam(Pointer, Constant, Param);
		}

		public void ClearParams()
		{
			GPUProgramUsage_ClearParams(Pointer);
		}
		public void SetBool(string Name, bool Value)
		{
			GPUProgramUsage_SetBool(Pointer, Name, Value);
		}
		public void SetInteger(string Name, int Value)
		{
			GPUProgramUsage_SetInteger(Pointer, Name, Value);
		}
		public void SetFloat(string Name, float Value)
		{
			GPUProgramUsage_SetFloat(Pointer, Name, Value);
		}
		public void SetVector2(string Name, Vector2 Value)
		{
			GPUProgramUsage_SetVector2(Pointer, Name, Value);
		}
		public void SetVector3(string Name, Vector3 Value)
		{
			GPUProgramUsage_SetVector3(Pointer, Name, Value);
		}
		public void SetMatrix(string Name, Matrix4 Value)
		{
			GPUProgramUsage_SetMatrix(Pointer, Name, Value);
		}
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_ClearAutoParams(IntPtr GPUProgramUsage);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetAutoParam(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Constant, [MarshalAs(UnmanagedType.BStr)] string Param);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_ClearParams(IntPtr GPUProgramUsage);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetBool(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, bool Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetInteger(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, int Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetFloat(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, float Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetVector2(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, Vector2 Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetVector3(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, Vector3 Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void GPUProgramUsage_SetMatrix(IntPtr GPUProgramUsage, [MarshalAs(UnmanagedType.BStr)] string Name, Matrix4 Value);
		
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr GPUProgramUsage_GetProgram(IntPtr GPUProgramUsage);
	}
}
