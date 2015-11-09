// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERTARGETTEXTURE_H
#define RENDERTARGETTEXTURE_H

#include <Private\RenderTarget.h>
#include <Private\Texture.h>

BEGIN_NAMESPACE

class RenderTargetTexture : public RenderTarget, public Texture
{
public:
	RenderTargetTexture(const Vector2 &Size, ColourFormats Format);
	virtual ~RenderTargetTexture(void) {}

	const Vector2 &GetSize(void) const
	{
		return Texture::GetSize();
	}

	Surface *GetSurface(void)
	{
		return Texture::GetSurface(0);
	}
};

END_NAMESPACE
#endif // RENDERTARGETTEXTURE_H
