// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef METAENUM_H
#define METAENUM_H
#include <Private\ImplementEnumType.h>
#include <Private\Specifiers.h>
#include <Private\Token.h>

BEGIN_NAMESPACE

class MetaEnum : public ImplementEnumType, public Specifiers
{
public:
	MetaEnum(void) :
		ImplementEnumType()
	{
	}
	~MetaEnum(void)
	{
	};
};

END_NAMESPACE
#endif // METAENUM_H
