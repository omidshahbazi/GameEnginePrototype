// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IDISTANCEJOINT_H
#define IDISTANCEJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IDistanceJoint : public IJoint
{
public:
	virtual ~IDistanceJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual void SetLength(float32 Value) = 0;
	virtual float32 GetLength(void) const = 0;

	virtual void SetDampingRatio(float32 Value) = 0;
	virtual float32 GetDampingRatio(void) const = 0;

	virtual void SetFrequency(float32 Value) = 0;
	virtual float32 GetFrequency(void) const = 0;

};

END_NAMESPACE
#endif // IDISTANCEJOINT_H
