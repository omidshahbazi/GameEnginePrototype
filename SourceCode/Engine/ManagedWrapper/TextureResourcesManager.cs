// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class TextureResourcesManager : ResourcesManager<TextureResourcesManager>
	{
		private static readonly TextureResourcesManager instance = new TextureResourcesManager();

		public static TextureResourcesManager Instance
		{
			get { return instance; }
		}

        private TextureResourcesManager() :
            base(TextureResourcesManager_GetPointer())
		{
		}

        public Texture GetTexture(string Name)
		{
            return WrapperObject.GetObject<Texture>(TextureResourcesManager_GetTexture(Name));
		}

        public Texture CreateTexture(string Name, Image Image, byte LevelsCount)
		{
            if (Image == null)
                return null;

            return new Texture(TextureResourcesManager_CreateTexture(Name, Image.Pointer, LevelsCount));
		}

        public RenderTarget CreateRenderTarget(string Name, Vector2 Size, Colour.Format Format)
        {
            return new RenderTarget(TextureResourcesManager_CreateRenderTarget(Name, Size, Format));
        }

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TextureResourcesManager_GetPointer();
        
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TextureResourcesManager_GetTexture([MarshalAs(UnmanagedType.BStr)] string Name);
        
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TextureResourcesManager_CreateTexture([MarshalAs(UnmanagedType.BStr)] string Name, IntPtr Image, byte LevelsCount);
        
		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TextureResourcesManager_CreateRenderTarget([MarshalAs(UnmanagedType.BStr)] string Name, Vector2 Size, Colour.Format Format);
	}
}
