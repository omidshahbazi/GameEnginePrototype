// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ITEXTURESOURCESFACTORY_H
#define ITEXTURESOURCESFACTORY_H

#include <Public\IResourcesFactory.h>
#include <Public\Renderer\ITexture.h>
#include <Public\Renderer\IRenderTarget.h>
#include <Public\Image.h>
#include <Public\Vector2.h>

BEGIN_NAMESPACE

class ITextureResourcesFactory : public IResourcesFactory
{
public:
	virtual ~ITextureResourcesFactory(void) {}

	virtual ITexture *CreateTexture(Image *Image, uint8 LevelsCount = 1) const = 0;
	virtual IRenderTarget *CreateRenderRarget(const Vector2 &Size, ColourFormats Format = ColourFormats::A8R8G8B8) const = 0;
};

END_NAMESPACE
#endif // ITEXTURESOURCESFACTORY_H
