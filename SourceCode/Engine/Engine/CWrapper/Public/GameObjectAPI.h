// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GAMEOBJECTAPI_H
#define GAMEOBJECTAPI_H
#include <Public\Utilities.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE

API_FUNCTION Component *GameObject_AddComponent(IGameObject *GameObject, BSTR TypeName);
API_FUNCTION Component *GameObject_GetComponent(IGameObject *GameObject, BSTR TypeName, IGameObject::FindComponentOption Option);

API_FUNCTION IScene *GameObject_GetHolder(IGameObject *GameObject);

API_FUNCTION void GameObject_SetName(IGameObject *GameObject, BSTR Name);
API_FUNCTION BSTR GameObject_GetName(IGameObject *GameObject);

API_FUNCTION void GameObject_SetTag(IGameObject *GameObject, uint32 Value);
API_FUNCTION uint32 GameObject_GetTag(IGameObject *GameObject);

API_FUNCTION void GameObject_SetVisible(IGameObject *GameObject, bool Visible);
API_FUNCTION bool GameObject_GetVisible(IGameObject *GameObject);

API_FUNCTION ITransform *GameObject_GetTransform(IGameObject *GameObject);


END_NAMESPACE
#endif // GAMEOBJECTAPI_H
