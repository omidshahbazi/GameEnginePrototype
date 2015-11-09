// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATERIALRESOURCESMANAGER_H
#define MATERIALRESOURCESMANAGER_H

#include <Public\Singleton.h>
#include <Public\ResourcesManager.h>
#include <Public\Renderer\IMaterialResourcesFactory.h>

BEGIN_NAMESPACE

class CORE_API MaterialResourcesManager : ResourcesManager
{
	DECLARE_SINGLETON(MaterialResourcesManager)

private:
	MaterialResourcesManager(void) {}

public:
	INLINE IMaterial *GetMaterial(const String &Name)
	{
		return (IMaterial*)GetOrLoadResource(Name);
	}
	INLINE IMaterial *CreateMaterial(const String &Name)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a Material named [" + Name + "]")

				return NULL;
		}

		IMaterial *mat = m_Factory->CreateMaterial();
		if (mat)
			AddResource(Name, mat);
		return mat;
	}

	INLINE void Initialize(IMaterialResourcesFactory *Factory)
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
	IMaterialResourcesFactory *m_Factory;
};

END_NAMESPACE
#endif // MATERIALRESOURCESMANAGER_H
