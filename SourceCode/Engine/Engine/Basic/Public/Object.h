// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef OBJECT_H
#define OBJECT_H

#include <Public\ReflectionDefinitions.h>
#include <Public\DataStructureType.h>

BEGIN_NAMESPACE

class BASIC_API Object
{
public:
	virtual ~Object(void) {}

	static void Destory(Object *Object);
};

END_NAMESPACE
#endif // OBJECT_H
