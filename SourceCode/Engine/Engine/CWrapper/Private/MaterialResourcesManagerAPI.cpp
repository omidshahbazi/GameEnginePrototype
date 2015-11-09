// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\MaterialResourcesManagerAPI.h>

BEGIN_NAMESPACE

MaterialResourcesManager *MaterialResourcesManager_GetPointer(void)
{
	return MaterialResourcesManager::GetPointer();
}


IMaterial *MaterialResourcesManager_GetMaterial(BSTR Name)
{
	return MaterialResourcesManager::GetReference().GetMaterial(TO_String(Name));
}


IMaterial *MaterialResourcesManager_CreateMaterial(BSTR Name)
{
	return MaterialResourcesManager::GetReference().CreateMaterial(TO_String(Name));
}


END_NAMESPACE
