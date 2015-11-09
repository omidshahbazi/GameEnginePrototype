// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\PluginManager.h>
#include <Public\Core.h>
#include <Public\IPlugin.h>
#include <Public\Exception.h>
#include <Public\Log.h>
#include <Public\Utility.h>
#include <Windows.h>

BEGIN_NAMESPACE

DEFINE_SINGLETON(PluginManager)

PluginManager::PluginManager(void)
{
}


PluginManager::~PluginManager(void)
{
	// We have not to destroy plugins here, it handled in Core::Close
}

	
void PluginManager::LoadPlugin(const String &FileName)
{
	HINSTANCE hInst = LoadLibraryEx(FileName.GetBuffer(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);

	if (hInst)
	{
		IPlugin *plugin = ((LoadPluginFunction)GetProcAddress(hInst, LOAD_PLUGIN_FUNCTION_STRING))();

		plugin->Install();

		m_Plugins.Add(plugin);

		LOG_INFO("Plugin [" + plugin->GetName() + " v" + plugin->GetVersion() + "] installed successfully")
	}
	else
	{
		THROW_EXCEPTION_AND_RESUME(Exception::ER_FILE_NOT_FOUND, "File [" + FileName + "] doesn't exists", "PluginManager::LoadPlugin")
	}
}

END_NAMESPACE
