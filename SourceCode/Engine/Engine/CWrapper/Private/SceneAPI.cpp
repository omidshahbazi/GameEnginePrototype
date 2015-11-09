// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\SceneAPI.h>


BEGIN_NAMESPACE


void Scene_Clear(IScene *Scene)
{
	Scene->Clear();
}


BSTR Scene_GetName(IScene *Scene)
{
	return TO_BSTR(Scene->GetName());
}


IGameObject *Scene_CreateGameObject(IScene *Scene, BSTR Name, ITransform *Parent)
{
	return Scene->CreateGameObject(TO_String(Name), Parent);
}


void Scene_DestroyGameObject(IScene *Scene, IGameObject *GameObject)
{
	return Scene->DestroyGameObject(GameObject);
}


void Scene_SetActive(IScene *Scene, bool Value)
{
	Scene->SetActive(Value);
}


bool Scene_GetActive(IScene *Scene)
{
	return Scene->GetActive();
}


END_NAMESPACE
