// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\RenderWindowAPI.h>


BEGIN_NAMESPACE


ICamera *RenderWindow_GetCamera(IRenderWindow *Window)
{
	return Window->GetCamera();
}


void RenderWindow_SetCamera(IRenderWindow *Window, ICamera *Camera)
{
	Window->SetCamera(Camera);
}


END_NAMESPACE
