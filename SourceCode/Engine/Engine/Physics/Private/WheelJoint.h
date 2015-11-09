// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef WHEELJOINT_H
#define WHEELJOINT_H

#include <Public\Physics\IWheelJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class WheelJoint : public IWheelJoint
{
public:
	WheelJoint(IPhysicsScene *Holder,
			   const String &Name,
			   IBody *BodyA,
			   IBody *BodyB,
			   bool CollideConnected = false,
			   const Vector2 &LocalAxisA = Vector2(0, 0),
			   const Vector2 &LocalAnchorA = Vector2(-1, 0),
			   const Vector2 &LocalAnchorB = Vector2(1, 0));

	virtual ~WheelJoint(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	const Vector2 &GetLocalAxisA(void) const
	{
		return m_LocalAxisA;
	}

	const Vector2 GetAnchorA(void) const;

	const Vector2 &GetLocalAnchorA(void) const
	{
		return m_LocalAnchorA;
	}

	const Vector2 GetAnchorB(void) const;

	const Vector2 &GetLocalAnchorB(void) const
	{
		return m_LocalAnchorB;
	}

	void EnableMotor(bool Flag);
	bool IsMotorEnabled(void) const
	{
		return m_IsMotorEnabled;
	}

	void SetMotorSpeed(float32 Value);
	float32 GetMotorSpeed(void) const
	{
		return m_MotorSpeed;
	}

	void SetMaxMotorTorque(float32 Value);
	float32 GetMaxMotorTorque(void) const
	{
		return m_MaxMotorTorque;
	}
	const float GetMotorTorque(float32 InverseDeltaTime) const
	{
		return m_Joint->GetMotorTorque(InverseDeltaTime);
	}

	void SetSpringFrequencyHz(float32 Value);
	float32 GetSpringFrequencyHz(void) const
	{
		return m_SpringFrequencyHz;
	}

	void SetSpringDampintRatio(float32 Value);
	float32 GetSpringDampingRatio(void) const
	{
		return m_SpringDampingRatio;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2WheelJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;
	Vector2 m_LocalAxisA;

	bool m_IsMotorEnabled;

	float m_MotorSpeed;
	float m_MaxMotorTorque;
	float m_SpringFrequencyHz;
	float m_SpringDampingRatio;
};

END_NAMESPACE
#endif // WHEELJOINT_H
