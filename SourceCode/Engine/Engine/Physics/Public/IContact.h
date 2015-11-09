// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICONTACT_H
#define ICONTACT_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class IFixture;

struct Vector2;

class IContact
{
public:
	virtual ~IContact(void) {}

	virtual IFixture *GetOtherFixture(void) = 0;

	virtual const Vector2 *GetPoints(void) = 0;

	virtual uint32 GetPointCount(void) = 0;

};

END_NAMESPACE
#endif // ICONTACT_H
