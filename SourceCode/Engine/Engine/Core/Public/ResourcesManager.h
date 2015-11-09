// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <Public\HashMap.h>
#include <Public\IResourcesFactory.h>

BEGIN_NAMESPACE

class CORE_API ResourcesManager
{
public:
	virtual ~ResourcesManager(void);

	void Reimport(void);

	INLINE bool HasResource(const String &Name) const
	{
		return m_Resources.ContainsKey(Name.ToLowerCase().Replace('\\', '/'));
	}

protected:
	virtual IResourcesFactory *GetFactory(void) const = 0;

	virtual Resource *GetOrLoadResource(const String &Name);
	virtual Resource *LoadResource(const String &Name);
	virtual Resource *GetResource(const String &Name);

	INLINE void AddResource(const String &Name, Resource *Resource)
	{
		const String name = Name.ToLowerCase();

		Resource->SetName(name);
		m_Resources[name] = Resource;
	}

private:
	typedef HashMap<String, Resource*> ResourcesMap;

	ResourcesMap m_Resources;
};

END_NAMESPACE
#endif // RESOURCESMANAGER_H
