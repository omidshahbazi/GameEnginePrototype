// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMATERIAL_H
#define IMATERIAL_H

#include <Public\Resource.h>
#include <Public\Renderer\IPass.h>

BEGIN_NAMESPACE
	
//<Description>
//This is sample description
class IMaterial : public Resource
{
public:
	typedef Vector<IPass*> PassesList;

public:
	virtual ~IMaterial(void) {}

	virtual IPass *CreatePass(void) = 0;

	virtual IPass *GetPass(uint8 Index) const = 0;
	virtual const PassesList &GetPasses(void) const = 0;
};

END_NAMESPACE
#endif // IMATERIAL_H
