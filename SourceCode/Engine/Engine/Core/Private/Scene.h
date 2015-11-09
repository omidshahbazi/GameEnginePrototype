// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SCENE_H
#define SCENE_H

#include <Public\IScene.h>
#include <Private\ComponentManager.h>
#include <Private\GameObject.h>
#include <Private\Transform.h>
#include <Public\Allocator.h>
#include <Private\SceneAllocationPolicy.h>

BEGIN_NAMESPACE

class Scene : public Allocator<SceneAllocationPolicy>, public IScene
{
public:
	Scene(const String &Name);
	virtual ~Scene(void);

	void Start(void)
	{
		m_ComponentManager.Start();
	}
	void PreUpdate(void)
	{
		m_ComponentManager.PreUpdate();
	}
	void Update(void)
	{
		m_ComponentManager.Update();
	}
	void PreRender(void)
	{
		m_ComponentManager.PreRender();
	}
	void Render(void)
	{
		m_ComponentManager.Render();
	}

	void Clear(void);

	void SetState(SceneStates State);
	SceneStates GetState(void)
	{
		return m_State;
	}

	const String &GetName(void) const
	{
		return m_Name;
	}

	IGameObject *CreateGameObject(const String &Name)
	{
		return CreateGameObject(Name, (Transform*)NULL);
	}
	IGameObject *CreateGameObject(const String &Name, IGameObject *Parent)
	{
		return CreateGameObject(Name, Parent == NULL ? NULL : Parent->GetTransform());
	}
	IGameObject *CreateGameObject(const String &Name, ITransform *Parent);
	void DestroyGameObject(IGameObject *GameObject);

	void SetActive(bool Value);
	bool GetActive(void) const
	{
		return m_Active;
	}

	ComponentManager *GetComponentManager(void)
	{
		return &m_ComponentManager;
	}

private:
	typedef Vector<IGameObject*> GameObjectsList;

	String m_Name;
	SceneStates m_State;
	ComponentManager m_ComponentManager;
	bool m_Active;

	GameObjectsList m_GameObjects;
};

END_NAMESPACE
#endif // SCENE_H
