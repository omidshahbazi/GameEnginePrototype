// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IREVOLUTEJOINT_H
#define IREVOLUTEJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IRevoluteJoint : public IJoint
{
public:
	virtual ~IRevoluteJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual const float32 GetJointAngle(void) const = 0;
	virtual float32 GetReferenceAngle(void) const = 0;

	virtual void EnableLimit(bool Flag) = 0;
	virtual bool IsLimitEnabled(void) const = 0;

	virtual void SetLimits(float32 LowerAngle, float32 UpperAngle) = 0;
	virtual void SetLowerLimit(float32 Value) = 0;
	virtual void SetUpperLimit(float32 Value) = 0;

	virtual float32 GetLowerLimit(void) const = 0;
	virtual float32 GetUpperLimit(void) const = 0;

	virtual void EnableMotor(bool Flag) = 0;
	virtual bool IsMotorEnabled(void) const = 0;

	virtual void SetMotorSpeed(float32 Value) = 0;
	virtual float32 GetMotorSpeed(void) const = 0;

	virtual void SetMaxMotorTorque(float32 Value) = 0;
	virtual const float32 GetMotorTorque(float32 InverseDeltaTime) const = 0;
	virtual float32 GetMaxMotorTorque(void) const = 0;
};

END_NAMESPACE
#endif // IREVOLUTEJOINT_H
