// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Scene.h>
#include <Public\Core.h>


BEGIN_NAMESPACE


Scene::Scene(const String &Name) :
m_Name(Name),
m_State(SceneStates::Stopped),
m_Active(true)
{
}


Scene::~Scene(void)
{
	Clear();
}


void Scene::Clear(void)
{
	//FOR_EACH(object, m_GameObjects)
	//	delete &object;
}


void Scene::SetState(SceneStates State)
{
	if (m_State == State && m_State == SceneStates::Playing)
	{
		LOG_ERROR("Before setting state of [" + m_Name + "] to Playing, you must set it to Stopped")
			return;
	}

	m_State = State;

	switch (m_State)
	{
	case SceneStates::Stopped:
	{
					   //CallFunctionOnGameObject(this, "End");

					   //ResetToInitializeState();
	} break;

	case SceneStates::Playing:
	{
					   //Core::GetReference().SetCurrentScene(this);

					   //SetInitializeState();

					   //CallFunctionOnGameObject(this, "Start");
	} break;
	}
}


IGameObject *Scene::CreateGameObject(const String &Name, ITransform *Parent)
{
	GameObject *obj = new GameObject(this, Name, Parent);

	m_GameObjects.Add(obj);

	return obj;
}

void Scene::DestroyGameObject(IGameObject *GameObject)
{
	m_GameObjects.Remove(GameObject);

	delete GameObject;
}


void Scene::SetActive(bool Value)
{
	if (m_Active == Value)
		return;

	m_Active = Value;

	//m_Scenes->SetActive(this, Value);
}

END_NAMESPACE
