// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMATERIALRESOURCESFACTORY_H
#define IMATERIALRESOURCESFACTORY_H

#include <Public\IResourcesFactory.h>
#include <Public\Renderer\IMaterial.h>

BEGIN_NAMESPACE

class IMaterialResourcesFactory : public IResourcesFactory
{
public:
	virtual ~IMaterialResourcesFactory(void) {}

	virtual IMaterial *CreateMaterial(void) const = 0;
};

END_NAMESPACE
#endif // IMATERIALRESOURCESFACTORY_H