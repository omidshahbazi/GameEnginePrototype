// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERTARGETAPI_H
#define RENDERTARGETAPI_H
#include <Public\Utilities.h>
#include <Public\IRenderTarget.h>
#include <Public\ICamera.h>

BEGIN_NAMESPACE

API_FUNCTION ICamera *RenderTarget_GetCamera(IRenderTarget *RenderTarget);
API_FUNCTION void RenderTarget_SetCamera(IRenderTarget *RenderTarget, ICamera *Camera);

END_NAMESPACE
#endif // RENDERTARGETAPI_H
