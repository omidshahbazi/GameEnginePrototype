// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERENGINEAPI_H
#define RENDERENGINEAPI_H
#include <Public\IRenderEngine.h>
#include <Public\Utilities.h>


BEGIN_NAMESPACE

API_FUNCTION IRenderWindow *RenderEngine_CreateRenderWindow(IRenderEngine *RenderEngine, WindowUtility::WindowHandle WindowHandle);

API_FUNCTION void RenderEngine_DestroyRenderWindow(IRenderEngine *RenderEngine, IRenderWindow *RenderWindow);

END_NAMESPACE
#endif // RENDERENGINEAPI_H
