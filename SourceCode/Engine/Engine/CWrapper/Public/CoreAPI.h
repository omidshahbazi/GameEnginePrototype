// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COREAPI_H
#define COREAPI_H
#include <Public\Utilities.h>
#include <Public\Core.h>

BEGIN_NAMESPACE

API_FUNCTION Core *Core_PreInitialize(void);

API_FUNCTION void Core_Initialize(Core *Core);

API_FUNCTION void Core_UpdateOneFrame(Core *Core);

API_FUNCTION FrameStats Core_GetFrameStats(Core *Core);

API_FUNCTION IScene *Core_CreateScene(Core *Core, BSTR Name);

API_FUNCTION IRenderEngine *Core_GetRenderer(Core *Core);

END_NAMESPACE
#endif // COREAPI_H
