// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RESOURCE_H
#define RESOURCE_H

#include <Public\ReferenceCounted.h>
#include <Public\Common.h>

BEGIN_NAMESPACE

class Resource : public ReferenceCounted
{
	friend class ResourcesManager;

public:
	virtual ~Resource(void) {}

	//virtual void Load(void) = 0;

	const String &GetName(void) const
	{
		return m_Name;
	}

private:
	void SetName(const String &Name)
	{
		m_Name = Name;
	}

private:
	String m_Name;
};

END_NAMESPACE
#endif // RESOURCE_H
