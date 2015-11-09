// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GameObject.h>
#include <Private\Transform.h>
#include <Private\Scene.h>
#include <Public\Line3d.h>
#include <Public\Core.h>
#include <Public\Runtime.h>


BEGIN_NAMESPACE


GameObject::GameObject(IScene *Holder, const String &Name, ITransform *Parent) :
m_Holder((Scene*)Holder),
m_Transform(NULL),
m_Name(Name),
m_Visible(Parent ? Parent->GetHolder()->GetVisible() : true),
m_Tag(0)
{
	m_Transform = new Transform(Parent);
	m_Holder->GetComponentManager()->AddComponent(m_Transform, this);
}


GameObject::~GameObject(void)
{
	m_Holder->GetComponentManager()->RemoveComponentsOf(this);
}


Component *GameObject::AddComponent(const String &Type)
{
	Component *com = Runtime::CreateInstance<Component>(Type);

	if (com)
		m_Holder->GetComponentManager()->AddComponent(com, this);

	return com;
}


Component *GameObject::GetComponent(const String &Type, FindComponentOptions Option)
{
	return m_Holder->GetComponentManager()->GetComponent(this, Type, Option);
}


void GameObject::GetComponents(ComponenetsList &List, const String &Type, FindComponentOptions Option)
{
	m_Holder->GetComponentManager()->GetComponents(List, this, Type, Option);
}

END_NAMESPACE
