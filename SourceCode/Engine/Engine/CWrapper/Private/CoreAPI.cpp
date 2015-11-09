// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\CoreAPI.h>

BEGIN_NAMESPACE


//
// For future plans, I return pointer of Core and i assume that we can create multiple instances from Core
//


Core *Core_PreInitialize(void)
{
	return Core::GetPointer();
}


void Core_Initialize(Core *Core)
{
	Core->Initialize();
}


void Core_UpdateOneFrame(Core *Core)
{
	Core->UpdateOneFrame();
}


FrameStats Core_GetFrameStats(Core *Core)
{
	return Core->GetFrameStats();
}


IScene *Core_CreateScene(Core *Core, BSTR Name)
{
	return Core->CreateScene(TO_String(Name));
}


IRenderEngine *Core_GetRenderer(Core *Core)
{
	return Core->GetRenderer();
}


END_NAMESPACE
