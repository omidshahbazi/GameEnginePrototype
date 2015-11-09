// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITERESOURCESMANAGER_H
#define COMPOSITERESOURCESMANAGER_H

#include <Public\Singleton.h>
#include <Public\ResourcesManager.h>
#include <Public\Renderer\ICompositeResourcesFactory.h>

BEGIN_NAMESPACE

class CORE_API CompositeResourcesManager : ResourcesManager
{
	DECLARE_SINGLETON(CompositeResourcesManager)

private:
	CompositeResourcesManager(void) {}

public:
	INLINE IComposite *GetCompoiste(const String &Name)
	{
		return (IComposite*)GetOrLoadResource(Name);
	}
	INLINE IComposite *CreateCompoiste(const String &Name)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a Material named [" + Name + "]")

				return NULL;
		}

		IComposite *com = m_Factory->CreateCompoiste();
		if (com)
			AddResource(Name, com);
		return com;
	}

	INLINE void Initialize(ICompositeResourcesFactory *Factory)
	{
		m_Factory = Factory;

		Reimport();
	}

private:
	INLINE IResourcesFactory *GetFactory(void) const
	{
		return m_Factory;
	}

private:
	ICompositeResourcesFactory *m_Factory;
};

END_NAMESPACE
#endif // COMPOSITERESOURCESMANAGER_H
