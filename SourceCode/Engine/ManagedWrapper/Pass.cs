// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Pass : WrapperObject
	{
		public enum FillMode
		{
			Point = 0,
			Wireframe,
			Solid
		};

		public enum CompareFunction
		{
			Never = 0,
			Less,
			Equal,
			LessEqual,
			Greater,
			NotEqual,
			GreaterEqual,
			Always
		};

		public enum BlendOperation
		{
			None = 0,
			Add,
			Min,
			Max,
			Subtrac,
			ReverseSubtrac
		};

		public enum BlendFactor
		{
			Zero = 0,
			One,
			DestinationColour,
			OneMinusDestinationColour,
			SourceColour,
			OneMinuesDestinationColour,
			SourceAlpha,
			OneMinusSourceAlpha,
			DestinationAlpha,
			OneMinusDestinationAlpha,
			SourceAlphaSaturate
		};

		public enum CullType
		{
			None = 0,
			Clockwise,
			CoClockwise
		};

		public FillMode FillModeType
		{
			get { return Pass_GetFillMode(Pointer); }
			set { Pass_SetFillMode(Pointer, value); }
		}

		public CompareFunction ZCompareFunction
		{
			get { return Pass_GetZCompareFunction(Pointer); }
			set { Pass_SetZCompareFunction(Pointer, value); }
		}

		public bool ZWrite
		{
			get { return Pass_GetZWrite(Pointer); }
			set { Pass_SetZWrite(Pointer, value); }
		}

		public BlendOperation BlendOperationType
		{
			get { return Pass_GetBlendOperation(Pointer); }
			set { Pass_SetBlendOperation(Pointer, value); }
		}

		public BlendFactor SourceBlendFactor
		{
			get { return Pass_GetSourceBlendFactor(Pointer); }
			set { Pass_SetSourceBlendFactor(Pointer, value); }
		}

		public BlendFactor DestinationBlendFactor
		{
			get { return Pass_GetDestinationBlendFactor(Pointer); }
			set { Pass_SetDestinationBlendFactor(Pointer, value); }
		}

		public CompareFunction AlphaTestFunction
		{
			get { return Pass_GetAlphaTestFunction(Pointer); }
			set { Pass_SetAlphaTestFunction(Pointer, value); }
		}

		public byte AlphaTestReference
		{
			get { return Pass_GetAlphaTestReference(Pointer); }
			set { Pass_SetAlphaTestReference(Pointer, value); }
		}

		public CullType CullTypeMode
		{
			get { return Pass_GetCullType(Pointer); }
			set { Pass_SetCullType(Pointer, value); }
		}

		public GPUProgram VertexProgram
		{
			get { return VertexProgramUsage.Program; }
			set { Pass_SetVertexProgram(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
		}

		public GPUProgram FragmentProgram
		{
			get { return FragmentProgramUsage.Program; }
			set { Pass_SetFragmentProgram(Pointer, value == null ? IntPtr.Zero : value.Pointer); }
		}

		public GPUProgramUsage VertexProgramUsage
		{
			get { return WrapperObject.GetObject<GPUProgramUsage>(Pass_GetVertexProgram(Pointer)); }
		}

		public GPUProgramUsage FragmentProgramUsage
		{
			get { return WrapperObject.GetObject<GPUProgramUsage>(Pass_GetFragmentProgram(Pointer)); }
		}
		
		public Pass(IntPtr Pointer) :
			base(Pointer)
		{
		}

		public Texture GetTextureStage(byte Stage)
		{
			return WrapperObject.GetObject<Texture>(Pass_GetTextureStage(Pointer, Stage));
		}

		public void SetTextureStage(byte Stage, Texture Texture)
		{
			Pass_SetTextureStage(Pointer, Stage, Texture == null ? IntPtr.Zero : Texture.Pointer);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetFillMode(IntPtr Pass, FillMode Mode);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern FillMode Pass_GetFillMode(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetZCompareFunction(IntPtr Pass, CompareFunction Function);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern CompareFunction Pass_GetZCompareFunction(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetZWrite(IntPtr Pass, bool Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.U1)]
		private static extern bool Pass_GetZWrite(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetBlendOperation(IntPtr Pass, BlendOperation Operation);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern BlendOperation Pass_GetBlendOperation(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetSourceBlendFactor(IntPtr Pass, BlendFactor Factor);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern BlendFactor Pass_GetSourceBlendFactor(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetDestinationBlendFactor(IntPtr Pass, BlendFactor Factor);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern BlendFactor Pass_GetDestinationBlendFactor(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetAlphaTestFunction(IntPtr Pass, CompareFunction Function);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern CompareFunction Pass_GetAlphaTestFunction(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetAlphaTestReference(IntPtr Pass, byte Reference);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern byte Pass_GetAlphaTestReference(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetCullType(IntPtr Pass, CullType Mode);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern CullType Pass_GetCullType(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetTextureStage(IntPtr Pass, byte Stage, IntPtr Texture);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Pass_GetTextureStage(IntPtr Pass, byte Stage);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetVertexProgram(IntPtr Pass, IntPtr Program);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Pass_GetVertexProgram(IntPtr Pass);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Pass_SetFragmentProgram(IntPtr Pass, IntPtr Program);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Pass_GetFragmentProgram(IntPtr Pass);
	}
}
