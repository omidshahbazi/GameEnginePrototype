// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SCENEAPI_H
#define SCENEAPI_H
#include <Public\Utilities.h>
#include <Public\IScene.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE

API_FUNCTION void Scene_Clear(IScene *Scene);

//API_FUNCTION void Scene_SetState(const SceneState &State) = 0;
//API_FUNCTION const Scene_SceneState &GetState(void) = 0;

API_FUNCTION BSTR Scene_GetName(IScene *Scene);

API_FUNCTION IGameObject *Scene_CreateGameObject(IScene *Scene, BSTR Name, ITransform *Parent);
API_FUNCTION void Scene_DestroyGameObject(IScene *Scene, IGameObject *GameObject);

API_FUNCTION void Scene_SetActive(IScene *Scene, bool Value);
API_FUNCTION bool Scene_GetActive(IScene *Scene);

END_NAMESPACE
#endif // SCENEAPI_H
