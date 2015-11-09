// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\TextureResourcesManagerAPI.h>

BEGIN_NAMESPACE

API_FUNCTION TextureResourcesManager *TextureResourcesManager_GetPointer(void)
{
	return TextureResourcesManager::GetPointer();
}


API_FUNCTION ITexture *TextureResourcesManager_GetTexture(BSTR Name)
{
	return TextureResourcesManager::GetReference().GetTexture(TO_String(Name));
}


API_FUNCTION ITexture *TextureResourcesManager_CreateTexture(BSTR Name, Image *Image, uint8 LevelsCount)
{
	return TextureResourcesManager::GetReference().CreateTexture(TO_String(Name), Image, LevelsCount);
}


API_FUNCTION IRenderTarget *TextureResourcesManager_CreateRenderTarget(BSTR Name, Vector2 Size, ColourFormats Format)
{
	return TextureResourcesManager::GetReference().CreateRenderTarget(TO_String(Name), Size, Format);
}


END_NAMESPACE
