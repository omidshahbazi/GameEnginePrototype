// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <Public\Common.h>
#include <Public\Singleton.h>

BEGIN_NAMESPACE

class IPlugin;

class CORE_API PluginManager
{
	DECLARE_SINGLETON(PluginManager)

private:
	PluginManager(void);
	~PluginManager(void);
	
public:
	void LoadPlugin(const String &FileName);
	
private:
	typedef Vector<IPlugin*> PluginsList;

	PluginsList m_Plugins;
};

END_NAMESPACE
#endif // PLUGINMANAGER_H
