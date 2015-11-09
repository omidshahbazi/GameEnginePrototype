// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\ComponentAPI.h>

BEGIN_NAMESPACE


bool Component_GetEnabled(Component *Component)
{
	return Component->GetEnabled();
}


void Component_SetEnabled(Component *Component, bool Value)
{
	Component->SetEnabled(Value);
}


IGameObject *Component_GetHolder(Component *Component)
{
	return Component->GetHolder();
}


END_NAMESPACE
