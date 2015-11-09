// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATERIALRESOURCESMANAGERAPI_H
#define MATERIALRESOURCESMANAGERAPI_H
#include <Public\Utilities.h>
#include <Public\MaterialResourcesManager.h>

BEGIN_NAMESPACE

API_FUNCTION MaterialResourcesManager *MaterialResourcesManager_GetPointer(void);

API_FUNCTION IMaterial *MaterialResourcesManager_GetMaterial(BSTR Name);
API_FUNCTION IMaterial *MaterialResourcesManager_CreateMaterial(BSTR Name);

END_NAMESPACE
#endif // MATERIALRESOURCESMANAGERAPI_H
