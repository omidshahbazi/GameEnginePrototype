// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\ResourcesManagerAPI.h>

BEGIN_NAMESPACE


void ResourcesManager_Reimport(ResourcesManager *ResourcesManager)
{
	ResourcesManager->Reimport();
}


bool ResourcesManager_HasResource(ResourcesManager *ResourcesManager, BSTR Name)
{
	return ResourcesManager->HasResource(TO_String(Name));
}


END_NAMESPACE
