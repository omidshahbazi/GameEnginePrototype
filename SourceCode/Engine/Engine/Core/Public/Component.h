// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPONENT_H
#define COMPONENT_H

#include <Public\Object.h>
#include <Public\Allocator.h>
#include <Private\SceneAllocationPolicy.h>
#include <Public\IGameObject.h>

BEGIN_NAMESPACE

class CORE_API Component : public Allocator<SceneAllocationPolicy>, public Object
{
	friend class ComponentManager;
	friend class GameObject;

public:
	Component(void) :
		m_Holder(NULL),
		m_Enabled(true)
	{
	}
	virtual ~Component(void) {}

	virtual void Awake(void) {}
	virtual void Destroy(void) {}
	virtual void Start(void) {}
	virtual void PreUpdate(void) {}
	virtual void Update(void) {}
	virtual void PreRender(void) {}
	virtual void Render(void) {}

	virtual bool GetEnabled(void) const
	{
		return m_Enabled;
	}
	virtual void SetEnabled(bool Value);

	IGameObject *GetHolder(void) const
	{
		return m_Holder;
	}

private:
	void SetHolder(IGameObject *Holder)
	{
		m_Holder = Holder;
	}

private:
	IGameObject *m_Holder;
	bool m_Enabled;
};

END_NAMESPACE
#endif // COMPONENT_H
