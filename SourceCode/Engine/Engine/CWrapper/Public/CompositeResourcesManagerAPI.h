// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITERESOURCESMANAGERAPI_H
#define COMPOSITERESOURCESMANAGERAPI_H
#include <Public\Utilities.h>
#include <Public\CompositeResourcesManager.h>

BEGIN_NAMESPACE

API_FUNCTION CompositeResourcesManager *CompositeResourcesManager_GetPointer(void);

API_FUNCTION IComposite *CompositeResourcesManager_GetComposite(BSTR Name);
API_FUNCTION IComposite *CompositeResourcesManager_CreateComposite(BSTR Name);

END_NAMESPACE
#endif // COMPOSITERESOURCESMANAGERAPI_H
