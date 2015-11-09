// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TEXTURERESOURCESMANAGERAPI_H
#define TEXTURERESOURCESMANAGERAPI_H
#include <Public\Utilities.h>
#include <Public\TextureResourcesManager.h>

BEGIN_NAMESPACE

API_FUNCTION TextureResourcesManager *TextureResourcesManager_GetPointer(void);

API_FUNCTION ITexture *TextureResourcesManager_GetTexture(BSTR Name);

API_FUNCTION ITexture *TextureResourcesManager_CreateTexture(BSTR Name, Image *Image, uint8 LevelsCount);

API_FUNCTION IRenderTarget *TextureResourcesManager_CreateRenderTarget(BSTR Name, Vector2 Size, ColourFormats Format);

END_NAMESPACE
#endif // TEXTURERESOURCESMANAGERAPI_H
