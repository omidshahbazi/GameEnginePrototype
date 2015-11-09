// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef REVOLUTEJOINT_H
#define REVOLUTEJOINT_H

#include <Public\Physics\IRevoluteJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class RevoluteJoint : public IRevoluteJoint
{
public:
	RevoluteJoint(IPhysicsScene *Holder,
				  const String &Name,
				  IBody *BodyA,
				  IBody *BodyB,
				  bool CollideConnected = false,
				  const Vector2 &LocalAnchorA = Vector2(0, 0),
				  const Vector2 &LocalAnchorB = Vector2(0, 0),
				  const float ReferenceAngle = 0);

	virtual ~RevoluteJoint(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

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

	const float GetJointAngle(void) const;
	float32 GetReferenceAngle(void) const
	{
		return m_ReferenceAngle;
	}

	void EnableLimit(bool Flag);
	bool IsLimitEnabled(void) const
	{
		return m_IsLimitEnabled;
	}

	void SetLimits(float32 LowerAngle, float32 UpperAngle);
	void SetLowerLimit(float32 Value);
	void SetUpperLimit(float32 Value);

	float32 GetLowerLimit(void) const
	{
		return m_LowerLimit;
	}
	float32 GetUpperLimit(void) const
	{
		return m_UpperLimit;
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

	void SetMaxMotorTorque(float32  Value);
	const float GetMotorTorque(float32 InverseDeltaTime) const;
	float32 GetMaxMotorTorque(void) const
	{
		return m_MaxMotorTorque;
	}

	b2RevoluteJoint *RevoluteJoint::GetBox2DJopint(void)
	{
		return m_Joint;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2RevoluteJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;

	bool m_IsLimitEnabled;
	bool m_IsMotorEnabled;

	float m_ReferenceAngle;
	float m_UpperLimit;
	float m_LowerLimit;
	float m_MotorSpeed;
	float m_MaxMotorTorque;
};

END_NAMESPACE
#endif // REVOLUTEJOINT_H
