// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\GameObjectAPI.h>


BEGIN_NAMESPACE


Component *GameObject_AddComponent(IGameObject *GameObject, BSTR TypeName)
{
	return GameObject->AddComponent(TO_String(TypeName));
}


Component *GameObject_GetComponent(IGameObject *GameObject, BSTR TypeName, IGameObject::FindComponentOption Option)
{
	return GameObject->GetComponent(TO_String(TypeName), Option);
}


IScene *GameObject_GetHolder(IGameObject *GameObject)
{
	return GameObject->GetHolder();
}

void GameObject_SetName(IGameObject *GameObject, BSTR Name)
{
	GameObject->SetName(TO_String(Name));
}


BSTR GameObject_GetName(IGameObject *GameObject)
{
	return TO_BSTR(GameObject->GetName());
}


void GameObject_SetTag(IGameObject *GameObject, uint32 Value)
{
	GameObject->SetTag(Value);
}


uint32 GameObject_GetTag(IGameObject *GameObject)
{
	return GameObject->GetTag();
}

void GameObject_SetVisible(IGameObject *GameObject, bool Visible)
{
	GameObject->SetVisible(Visible);
}


bool GameObject_GetVisible(IGameObject *GameObject)
{
	return GameObject->GetVisible();
}


ITransform *GameObject_GetTransform(IGameObject *GameObject)
{
	return GameObject->GetTransform();
}


END_NAMESPACE
