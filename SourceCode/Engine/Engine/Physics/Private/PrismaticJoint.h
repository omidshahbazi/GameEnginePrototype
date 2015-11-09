// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PRISMATICJOINT_H
#define PRISMATICJOINT_H

#include <Public\Physics\IPrismaticJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class PrismaticJoint : public IPrismaticJoint
{
public:
	PrismaticJoint(IPhysicsScene *Holder,
				   const String &Name,
				   IBody *BodyA,
				   IBody *BodyB,
				   bool CollideConnected = false,
				   const Vector2 &LocalAxisA = Vector2(0, 0),
				   const Vector2 &LocalAnchorA = Vector2(0, 0),
				   const Vector2 &LocalAnchorB = Vector2(0, 0),
				   const float ReferenceAngle = 0);

	virtual ~PrismaticJoint(void);

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

	void SetMaxMotorForce(float32 Value);
	float32 GetMaxMotorForce(void) const
	{
		return m_MaxMotorForce;
	}
	const float GetMotorForce(float32 InverseDeltaTime) const;

	b2PrismaticJoint *GetBox2DJopint(void);

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2PrismaticJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;
	Vector2 m_LocalAxisA;

	bool m_IsLimitEnabled;
	bool m_IsMotorEnabled;

	float m_ReferenceAngle;
	float m_UpperLimit;
	float m_LowerLimit;
	float m_MotorSpeed;
	float m_MaxMotorForce;
};

END_NAMESPACE
#endif // PRISMATICJOINT_H
