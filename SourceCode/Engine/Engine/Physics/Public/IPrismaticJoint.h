// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPRISMATICJOINT_H
#define IPRISMATICJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IPrismaticJoint : public IJoint
{
public:
	virtual ~IPrismaticJoint(void) {}

	virtual const Vector2 &GetLocalAxisA(void) const = 0;

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

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

	virtual void SetMaxMotorForce(float32 Value) = 0;
	virtual float32 GetMaxMotorForce(void) const = 0;
	virtual const float32 GetMotorForce(float32 InverseDeltaTime) const = 0;

};

END_NAMESPACE
#endif // IPRISMATICJOINT_H
