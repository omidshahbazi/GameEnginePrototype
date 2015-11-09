// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERWINDOWAPI_H
#define RENDERWINDOWAPI_H
#include <Public\ICamera.h>
#include <Public\IRenderWindow.h>
#include <Public\Utilities.h>


BEGIN_NAMESPACE

API_FUNCTION ICamera *RenderWindow_GetCamera(IRenderWindow *Window);
API_FUNCTION void RenderWindow_SetCamera(IRenderWindow *Window, ICamera *Camera);

END_NAMESPACE
#endif // RENDERWINDOWAPI_H
