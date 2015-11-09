// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RESOURCESMANAGERAPI_H
#define RESOURCESMANAGERAPI_H
#include <Public\Utilities.h>
#include <Public\ResourcesManager.h>

BEGIN_NAMESPACE

API_FUNCTION void ResourcesManager_Reimport(ResourcesManager *ResourcesManager);
API_FUNCTION bool ResourcesManager_HasResource(ResourcesManager *ResourcesManager, BSTR Name);

END_NAMESPACE
#endif // RESOURCESMANAGERAPI_H
