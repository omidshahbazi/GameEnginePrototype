// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <Public\Component.h>
#include <Public\IGameObject.h>
#include <Public\ActiveVector.h>

BEGIN_NAMESPACE

class ComponentManager
{
public:
	ComponentManager(void);
	~ComponentManager(void);

	void Start(void);
	void PreUpdate(void);
	void Update(void);
	void PreRender(void);
	void Render(void);

	void AddComponent(Component *Component, IGameObject *Holder);
	void RemoveComponent(Component *Component);
	void RemoveComponentsOf(IGameObject *Holder);

	Component *GetComponent(IGameObject *Holder, const String &Type, FindComponentOptions Option);
	void GetComponents(IGameObject::ComponenetsList &List, IGameObject *Holder, const String &Type, FindComponentOptions Option);

	void SetEnabled(Component *Component, bool Value)
	{
		m_Components.SetActive(Component, Value);
	}

private:
	typedef ActiveVector<Component*> ComponentList;

	ComponentList m_Components;
};

END_NAMESPACE
#endif // COMPONENTMANAGER_H
