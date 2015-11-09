// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IROPEJOINT_H
#define IROPEJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IRopeJoint : public IJoint
{
public:
	virtual ~IRopeJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual void SetMaxLength(float32 Value) = 0;
	virtual float32 GetMaxLength(void) const = 0;
};

END_NAMESPACE
#endif // IROPEJOINT_H
