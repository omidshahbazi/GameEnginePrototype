// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Public\IGameObject.h>
#include <Public\Core.h>
#include <Private\Scene.h>
#include <Private\Transform.h>

BEGIN_NAMESPACE

class GameObject : public Allocator<SceneAllocationPolicy>, public IGameObject
{
	friend class Scene;

public:
	GameObject(IScene *Holder, const String &Name, ITransform *Parent = NULL);
	virtual ~GameObject(void);

	template<class T> T *AddComponent(void)
	{
		return (T*)AddComponent(T::GetType().GetName());
	}
	template<class T> T *AddComponent(const String &Type)
	{
		return (T*)AddComponent(Type);
	}
	Component *AddComponent(const String &Type);

	template<class T> T *GetComponent(FindComponentOptions Option = FindComponentOptions::Active)
	{
		return (T*)GetComponent(T::GetType().GetName(), Option);
	}
	template<class T> T *GetComponent(const String &Type, FindComponentOptions Option = FindComponentOptions::Active)
	{
		return (T*)GetComponent(Type, Option);
	}
	Component *GetComponent(const String &Type, FindComponentOptions Option = FindComponentOptions::Active);

	template<class T> void GetComponents(ComponenetsList &List, FindComponentOptions Option = FindComponentOptions::Active)
	{
		GetComponents(List, T::GetType().GetName, Option);
	}
	void GetComponents(ComponenetsList &List, const String &Type, FindComponentOptions Option = FindComponentOptions::Active);

	IScene *GetHolder(void)
	{
		return (IScene*)m_Holder;
	}

	void SetName(const String &Name)
	{
		m_Name = Name;
	}

	const String &GetName(void) const
	{
		return m_Name;
	}

	void SetTag(uint32 Value)
	{
		m_Tag = Value;
	}
	uint32 GetTag(void) const
	{
		return m_Tag;
	}

	void SetVisible(bool Visible)
	{
		m_Visible = Visible;
	}
	bool GetVisible(void) const
	{
		return m_Visible;
	}

	ITransform *GetTransform(void)
	{
		return m_Transform;
	}

private:
	Scene *m_Holder;
	String m_Name;
	uint32 m_Tag;
	bool m_Visible;
	Transform *m_Transform;
};

END_NAMESPACE
#endif // GAMEOBJECT_H
