// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICOMPOSITE_H
#define ICOMPOSITE_H
#include <Public\Resource.h>
#include <Public\Renderer\ICompositePass.h>
#include <Public\Colour.h>

BEGIN_NAMESPACE

class IRenderTarget;

class IComposite : public Resource
{
public:
	typedef Vector<ICompositePass*> PassesList;

public:
	virtual ~IComposite(void) {}

	virtual ICompositePass *CreatePass(void) = 0;
	virtual ICompositePass *GetPass(uint8 Index) const = 0;
	virtual const PassesList &GetPasses(void) const = 0;
};

END_NAMESPACE
#endif // ICOMPOSITE_H
