// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IRESOURCESFACTORY_H
#define IRESOURCESFACTORY_H

#include <Public\Resource.h>

BEGIN_NAMESPACE

class IResourcesFactory
{
public:
	virtual ~IResourcesFactory(void) {}

	virtual Resource *LoadResource(const String &Name) const = 0;

	virtual const String &GetSupportedExtensions(void) const = 0;
	virtual bool IsExtensionSupported(const String &Extension) const = 0;
};

END_NAMESPACE
#endif // IResourcesFactory_H
