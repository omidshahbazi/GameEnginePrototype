// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\RenderTargetAPI.h>

BEGIN_NAMESPACE


ICamera *RenderTarget_GetCamera(IRenderTarget *RenderTarget)
{
	return RenderTarget->GetCamera();
}


void RenderTarget_SetCamera(IRenderTarget *RenderTarget, ICamera *Camera)
{
	RenderTarget->SetCamera(Camera);
}


END_NAMESPACE
