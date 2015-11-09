// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\ResourcesManager.h>
#include <Public\Core.h>
#include <Public\Utility.h>
#include <Public\StringUtility.h>


BEGIN_NAMESPACE


ResourcesManager::~ResourcesManager(void)
{
}


void ResourcesManager::Reimport(void)
{
	StringsList list;

	static const String &dataPath = Core::GetReference().GetDataPath();

	Utility::GetFiles(list, dataPath, true, GetFactory()->GetSupportedExtensions());

	FOR_EACH(file, list)
		m_Resources[file->Replace(dataPath, "").Replace('\\', '/').ToLowerCase()] = NULL;
}


Resource *ResourcesManager::GetOrLoadResource(const String &Name)
{
	Resource *res = GetResource(Name);

	if (res)
		return res;

	return LoadResource(Name);
}


Resource *ResourcesManager::LoadResource(const String &Name)
{
	const String name = Name.ToLowerCase().Replace('\\', '/');

	if (HasResource(name) && m_Resources[name] != NULL)
	{
		LOG_ERROR("Resource named [" + Name + "] already loaded");

		return NULL;
	}

	Resource *res = GetFactory()->LoadResource(name);
	m_Resources[name] = res;

	if (res)
		res->SetName(Name);

	return res;
}


Resource *ResourcesManager::GetResource(const String &Name)
{
	const String name = Name.ToLowerCase().Replace('\\', '/');

	//if (!HasResource(name))
	//{
	//	LOG_ERROR("Resource named [" + Name + "] doesn't exists");

	//	return NULL;
	//}

	return m_Resources[name];
}


END_NAMESPACE
