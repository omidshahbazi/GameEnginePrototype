// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include <Public\Renderer\ITextureResourcesFactory.h>
#include <Private\Texture.h>
#include <Private\RenderTargetTexture.h>
#include <Private\RendererCommon.h>

BEGIN_NAMESPACE

const String Supported_Extensions("png;jpg;tga;tiff;gif;psd;raw");

class TextureResourcesFactory : public ITextureResourcesFactory
{
private:
	Resource *LoadResource(const String &Name) const
	{
		static const String &dataPath = Core::GetReference().GetDataPath();

		Image img;
		if (!img.Load(dataPath + Name))
			return NULL;

		return CreateTexture(&img);
	}

	ITexture *CreateTexture(Image *Image, uint8 LevelsCount = 1) const
	{
		return new Texture(Image, LevelsCount);
	}

	IRenderTarget *CreateRenderRarget(const Vector2 &Size, ColourFormats Format = ColourFormats::A8R8G8B8) const
	{
		static RenderEngine *engine = (RenderEngine*)Core::GetReference().GetRenderer();

		RenderTargetTexture *rtt = new RenderTargetTexture(Size, Format);
		engine->AddRenderTarget(rtt);
		return rtt;
	}

	const String &GetSupportedExtensions(void) const
	{
		return Supported_Extensions;
	}

	bool IsExtensionSupported(const String &Extension) const
	{
		return Supported_Extensions.Find(Extension) > -1;
	}
};

END_NAMESPACE
#endif // TEXTUREFACTORY_H
