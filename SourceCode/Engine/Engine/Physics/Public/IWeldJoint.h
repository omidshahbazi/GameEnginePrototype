// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IWELDJOINT_H
#define IWELDJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IWeldJoint : public IJoint
{
public:
	virtual ~IWeldJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual float32 GetReferenceAngle(void) const = 0;

	virtual void SetFrequencyHz(float32 Value) = 0;
	virtual float32 GetFrequencyHz(void) const = 0;

	virtual void SetDampintRatio(float32 Value) = 0;
	virtual float32 GetDampingRatio(void) const = 0;

};

END_NAMESPACE
#endif // IWELDJOINT_H
