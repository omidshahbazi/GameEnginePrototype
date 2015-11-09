// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef METAPROPERTY_H
#define METAPROPERTY_H
#include <Private\ImplementPropertyType.h>
#include <Private\Specifiers.h>

BEGIN_NAMESPACE

class MetaProperty : public ImplementPropertyType, public Specifiers
{
public:
	MetaProperty(Type *TopNest) :
		ImplementPropertyType(TopNest)
	{
	}
	~MetaProperty(void)
	{
	}
};

END_NAMESPACE
#endif // METAPROPERTY_H
