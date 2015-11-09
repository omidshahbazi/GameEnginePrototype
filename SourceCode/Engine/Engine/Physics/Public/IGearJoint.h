// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGEARJOINT_H
#define IGEARJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IRevoluteJoint;
class IPrismaticJoint;

class IGearJoint : public IJoint
{
public:
	virtual ~IGearJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual void SetRatio(float32 Value) = 0;
	virtual float32 GetRatio(void) const = 0;

	virtual IRevoluteJoint *GetRevoluteJoint(void) = 0;

	virtual IPrismaticJoint *GetPrismaticJoint(void) = 0;
};

END_NAMESPACE
#endif // IGEARJOINT_H
