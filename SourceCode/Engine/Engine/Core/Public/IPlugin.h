// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class IPlugin
{
	friend class PluginManager;

protected:
	virtual ~IPlugin(void) {}

	virtual void Install(void) = 0;

	virtual const String &GetName(void) const = 0;
	
	virtual const String &GetVersion(void) const = 0;
};

END_NAMESPACE

USING_NAMESPACE

#define LOAD_PLUGIN_FUNCTION LoadPlugin

#define LOAD_PLUGIN_FUNCTION_STRING "LoadPlugin"

#define BEGIN_LOAD_PLUGIN_DEFINITION EXTERN_C DLL_EXPORT IPlugin *LOAD_PLUGIN_FUNCTION(void) \
										{
#define END_LOAD_PLUGIN_DEFINITION	}

typedef IPlugin* (*LoadPluginFunction)(void);

#endif // IPLUGIN_H