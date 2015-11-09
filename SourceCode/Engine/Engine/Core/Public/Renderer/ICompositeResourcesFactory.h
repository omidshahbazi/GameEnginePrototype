// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICOMPOSITERESOURCESFACTORY_H
#define ICOMPOSITERESOURCESFACTORY_H

#include <Public\IResourcesFactory.h>
#include <Public\Renderer\IComposite.h>

BEGIN_NAMESPACE

class ICompositeResourcesFactory : public IResourcesFactory
{
public:
	virtual ~ICompositeResourcesFactory(void) {}

	virtual IComposite *CreateCompoiste(void) const = 0;
};

END_NAMESPACE
#endif // ICOMPOSITERESOURCESFACTORY_H
