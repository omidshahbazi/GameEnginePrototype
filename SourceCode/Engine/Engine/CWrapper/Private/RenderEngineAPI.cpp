// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\RenderEngineAPI.h>


BEGIN_NAMESPACE


IRenderWindow *RenderEngine_CreateRenderWindow(IRenderEngine *RenderEngine, WindowUtility::WindowHandle WindowHandle)
{
	return RenderEngine->CreateRenderWindow(WindowHandle);
}


void RenderEngine_DestroyRenderWindow(IRenderEngine *RenderEngine, IRenderWindow *RenderWindow)
{
	RenderEngine->DestroyRenderWindow(RenderWindow);
}


END_NAMESPACE
