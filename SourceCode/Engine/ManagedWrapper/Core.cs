// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Core : WrapperObject
	{
		private RenderEngine renderEngine;

		public RenderEngine RenderEngine
		{
			get { return renderEngine; }
		}

		public FrameStats FrameStats
        {
			get { return Core_GetFrameStats(Pointer); }
        }

		public Core() :
			base(Core_PreInitialize())
		{
		}

		public void Initialize()
		{
			Core_Initialize(Pointer);

			renderEngine = new RenderEngine(Core_GetRenderer(Pointer));
		}

		public void UpdateOneFrame()
		{
			Core_UpdateOneFrame(Pointer);
		}

		public Scene CreateScene(string Name)
		{
			return new Scene(Core_CreateScene(Pointer, Name), Name);
		}

		[DllImport(Constants.CWrapperDLL)]
		private static extern IntPtr Core_PreInitialize();

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Core_Initialize(IntPtr Core);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Core_UpdateOneFrame(IntPtr Core);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern FrameStats Core_GetFrameStats(IntPtr Core);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Core_CreateScene(IntPtr Core, [MarshalAs(UnmanagedType.BStr)] string Name);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Core_GetRenderer(IntPtr Core);
	}
}
