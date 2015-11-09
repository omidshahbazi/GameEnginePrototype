// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPONENTAPI_H
#define COMPONENTAPI_H
#include <Public\Utilities.h>
#include <Public\Component.h>

BEGIN_NAMESPACE

API_FUNCTION bool Component_GetEnabled(Component *Component);

API_FUNCTION void Component_SetEnabled(Component *Component, bool Value);

API_FUNCTION IGameObject *Component_GetHolder(Component *Component);

END_NAMESPACE
#endif // COMPONENTAPI_H
