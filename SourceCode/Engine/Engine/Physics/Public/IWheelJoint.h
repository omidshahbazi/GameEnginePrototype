// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IWHEELJOINT_H
#define IWHEELJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IWheelJoint : public IJoint
{
public:
	virtual ~IWheelJoint(void) {}

	virtual const Vector2 &GetLocalAxisA(void) const = 0;

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual void EnableMotor(bool Flag) = 0;
	virtual bool IsMotorEnabled(void) const = 0;

	virtual void SetMotorSpeed(float32 Value) = 0;
	virtual float32 GetMotorSpeed(void) const = 0;

	virtual void SetMaxMotorTorque(float32 Value) = 0;
	virtual float32 GetMaxMotorTorque(void) const = 0;
	virtual const float32 GetMotorTorque(float32 InverseDeltaTime) const = 0;

	virtual void SetSpringFrequencyHz(float32 Value) = 0;
	virtual float32 GetSpringFrequencyHz(void) const = 0;

	virtual void SetSpringDampintRatio(float32 Value) = 0;
	virtual float32 GetSpringDampingRatio(void) const = 0;

};

END_NAMESPACE
#endif // IWHEELJOINT_H
