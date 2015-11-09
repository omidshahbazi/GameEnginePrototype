// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\RenderTargetTexture.h>
#include <Private\RenderEngine.h>
#include <Private\RendererCommon.h>
#include <Public\Core.h>

BEGIN_NAMESPACE


RenderTargetTexture::RenderTargetTexture(const Vector2 &Size, ColourFormats Format) :
Texture(Size, Format)
{
	//if (!GetNativeTexture())
	//	RenderTarget::Drop();
}


END_NAMESPACE
