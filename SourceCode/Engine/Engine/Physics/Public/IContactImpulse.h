// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICONTACTIMPULSE_H
#define ICONTACTIMPULSE_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class IFixture;

struct Vector2;

class IContactImpulse
{
public:
	virtual ~IContactImpulse(void) {}

	virtual uint32 GetImpulseCount(void) = 0;

	virtual const float32 *GetNormalImpulse(void) = 0;

	virtual const float32 *GetTangentImpulse(void) = 0;
};

END_NAMESPACE
#endif // ICONTACTIMPULSE_H
