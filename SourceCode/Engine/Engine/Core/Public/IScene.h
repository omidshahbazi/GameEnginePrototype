// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ISCENE_H
#define ISCENE_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class IGameObject;
class ITransform;
class ICamera;

enum SceneStates
{
	Stopped = 0,
	Playing
};

class IScene
{
public:
	virtual ~IScene(void) {}

	virtual void Start(void) = 0;
	virtual void PreUpdate(void) = 0;
	virtual void Update(void) = 0;
	virtual void PreRender(void) = 0;
	virtual void Render(void) = 0;

	virtual void Clear(void) = 0;

	virtual void SetState(SceneStates State) = 0;
	virtual SceneStates GetState(void) = 0;

	virtual const String &GetName(void) const = 0;

	virtual IGameObject *CreateGameObject(const String &Name) = 0;
	virtual IGameObject *CreateGameObject(const String &Name, IGameObject *Parent) = 0;
	virtual IGameObject *CreateGameObject(const String &Name, ITransform *Parent) = 0;
	virtual void DestroyGameObject(IGameObject *GameObject) = 0;

	virtual void SetActive(bool Value) = 0;
	virtual bool GetActive(void) const = 0;
};

END_NAMESPACE
#endif // ISCENE_H