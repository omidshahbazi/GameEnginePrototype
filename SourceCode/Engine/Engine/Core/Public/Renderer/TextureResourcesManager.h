// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TEXTURERESOURCESMANAGER_H
#define TEXTURERESOURCESMANAGER_H

#include <Public\Singleton.h>
#include <Public\ResourcesManager.h>
#include <Public\Renderer\ITextureResourcesFactory.h>

BEGIN_NAMESPACE

class CORE_API TextureResourcesManager : ResourcesManager
{
	DECLARE_SINGLETON(TextureResourcesManager)

private:
	TextureResourcesManager(void) {}

public:
	INLINE ITexture *CreateTexture(const String &Name, Image *Image, uint8 LevelsCount = 1)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a Texture named [" + Name + "]")

				return NULL;
		}

		ITexture *tex = m_Factory->CreateTexture(Image, LevelsCount);
		if (tex)
			AddResource(Name, tex);
		return tex;
	}

	INLINE IRenderTarget *CreateRenderTarget(const String &Name, const Vector2 &Size, ColourFormats Format = ColourFormats::A8R8G8B8)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a Texture named [" + Name + "]")

				return NULL;
		}

		IRenderTarget *rt = m_Factory->CreateRenderRarget(Size, Format);
		if (rt)
			AddResource(Name, rt);
		return rt;
	}

	INLINE ITexture *GetTexture(const String &Name)
	{
		return (ITexture*)GetOrLoadResource(Name);
	}

	INLINE void Initialize(ITextureResourcesFactory *Factory)
	{
		m_Factory = Factory;

		Reimport();
	}

private:
	INLINE IResourcesFactory *GetFactory(void) const
	{
		return m_Factory;
	}

private:
	ITextureResourcesFactory *m_Factory;
};

END_NAMESPACE
#endif // TEXTURERESOURCESMANAGER_H
