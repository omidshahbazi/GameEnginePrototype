// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\CompositeResourcesManagerAPI.h>

BEGIN_NAMESPACE

CompositeResourcesManager *CompositeResourcesManager_GetPointer(void)
{
	return CompositeResourcesManager::GetPointer();
}


IComposite *CompositeResourcesManager_GetComposite(BSTR Name)
{
	return CompositeResourcesManager::GetReference().GetCompoiste(TO_String(Name));
}


IComposite *CompositeResourcesManager_CreateComposite(BSTR Name)
{
	return CompositeResourcesManager::GetReference().CreateCompoiste(TO_String(Name));
}


END_NAMESPACE
