// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ComponentManager.h>
#include <Public\Component.h>
#include <Private\ScriptSystem.h>


BEGIN_NAMESPACE


#define CALL_COMPONENTS_FUNCTION(FunctionName) \
for (uint32 i = 0; i < m_Components.GetActiveCount(); i++) \
	m_Components[i]->FunctionName();


ComponentManager::ComponentManager(void) :
m_Components(100)
{
}


ComponentManager::~ComponentManager(void)
{
}


void ComponentManager::Start(void)
{
	CALL_COMPONENTS_FUNCTION(Start)
}


void ComponentManager::PreUpdate(void)
{
	CALL_COMPONENTS_FUNCTION(PreUpdate)
}


void ComponentManager::Update(void)
{
	CALL_COMPONENTS_FUNCTION(Update)
}


void ComponentManager::PreRender(void)
{
	CALL_COMPONENTS_FUNCTION(PreRender)
}


void ComponentManager::Render(void)
{
	CALL_COMPONENTS_FUNCTION(Render)
}


void ComponentManager::AddComponent(Component *Component, IGameObject *Holder)
{
	if (Component->GetHolder())
		return;

	m_Components.Add(Component);

	Component->SetHolder(Holder);
	Component->Awake();
}


void ComponentManager::RemoveComponent(Component *Component)
{
	m_Components.Remove(Component);

	Component->Destroy();

	delete Component;
}


void ComponentManager::RemoveComponentsOf(IGameObject *Holder)
{
	IGameObject::ComponenetsList list;

	uint32 i;
	for (i = 0; i < m_Components.GetSize(); i++)
	{
		Component *com = m_Components[i];

		if (com->GetHolder() == Holder)
			list.Add(com);
	}

	for (i = 0; i < list.GetSize(); i++)
		RemoveComponent(list[i]);
}


Component *ComponentManager::GetComponent(IGameObject *Holder, const String &Type, FindComponentOptions Option)
{
	uint32 i = (Option == FindComponentOptions::Deactive ? m_Components.GetInactiveStartIndex() : 0);
	const uint32 count = (Option == FindComponentOptions::Active ? m_Components.GetInactiveStartIndex() : (Option == FindComponentOptions::All ? m_Components.GetSize() : m_Components.GetInactiveCount()));

	for (; i < count; i++)
	{
		Component *com = m_Components[i];

		//if (com->GetHolder() == Holder && com->GetTypeInfo() == Type)
		//	return com;
	}

	return NULL;
}


void ComponentManager::GetComponents(IGameObject::ComponenetsList &List, IGameObject *Holder, const String &Type, FindComponentOptions Option)
{
	uint32 i = (Option == FindComponentOptions::Deactive ? m_Components.GetActiveCount() : 0);
	const uint32 count = (Option == FindComponentOptions::Active ? m_Components.GetInactiveStartIndex() : (Option == FindComponentOptions::All ? m_Components.GetSize() : m_Components.GetInactiveCount()));

	for (; i < count; i++)
	{
		Component *com = m_Components[i];

		//if (com->GetHolder() == Holder && com->GetTypeInfo() == Type)
		//	List.Add(com);
	}
}

END_NAMESPACE
