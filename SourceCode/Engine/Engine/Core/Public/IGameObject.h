// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <Public\Object.h>

BEGIN_NAMESPACE

class ITransform;
class IScene;
class Component;

REFLECTION_ENUM()
enum class FindComponentOptions
{
	Active = 0,
	Deactive,
	All
};

class IGameObject : public Object
{
public:
	typedef Vector<Component*> ComponenetsList;

public:
	virtual ~IGameObject(void) {}

	template<class T> T *AddComponent(void)
	{
		return (T*)AddComponent(T::GetType().GetName());
	}
	template<class T> T *AddComponent(const String &Type)
	{
		return (T*)AddComponent(Type);
	}
	virtual Component *AddComponent(const String &Type) = 0;

	template<class T> T *GetComponent(FindComponentOptions Option = FindComponentOptions::Active)
	{
		return (T*)GetComponent(T::GetType().GetName(), Option);
	}
	template<class T> T *GetComponent(const String &Type, FindComponentOptions Option = FindComponentOptions::Active)
	{
		return (T*)GetComponent(Type, Option);
	}
	virtual Component *GetComponent(const String &Type, FindComponentOptions Option = FindComponentOptions::Active) = 0;

	template<class T> void GetComponents(ComponenetsList &List, FindComponentOptions Option = FindComponentOptions::Active)
	{
		GetComponents(List, T::GetType().GetName, Option);
	}
	virtual void GetComponents(ComponenetsList &List, const String &Type, FindComponentOptions Option = FindComponentOptions::Active) = 0;

	virtual IScene *GetHolder(void) = 0;

	virtual void SetName(const String &Name) = 0;
	virtual const String &GetName(void) const = 0;

	virtual void SetTag(uint32 Value) = 0;
	virtual uint32 GetTag(void) const = 0;

	virtual void SetVisible(bool Visible) = 0;
	virtual bool GetVisible(void) const = 0;

	virtual ITransform *GetTransform(void) = 0;
};

END_NAMESPACE
#endif // IGAMEOBJECT_H
