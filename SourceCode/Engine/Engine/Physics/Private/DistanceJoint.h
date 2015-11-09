// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef DISTANCEJOINT_H
#define DISTANCEJOINT_H

#include <Public\Physics\IDistanceJoint.h>
#include <Private\PhysicsCommon.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class DistanceJoint : public IDistanceJoint
{
public:
	DistanceJoint(IPhysicsScene *Holder,
				  const String &Name,
				  IBody *BodyA,
				  IBody *BodyB,
				  bool CollideConnected = false,
				  const Vector2 &LocalAnchorA = Vector2(0, 0),
				  const Vector2 &LocalAnchorB = Vector2(0, 0));

	virtual ~DistanceJoint(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	const Vector2 GetAnchorA(void) const
	{
		return ToVector2(m_Joint->GetAnchorA());
	}

	const Vector2 &GetLocalAnchorA(void) const
	{
		return m_LocalAnchorA;
	}

	const Vector2 GetAnchorB(void) const
	{
		return ToVector2(m_Joint->GetAnchorB());
	}

	const Vector2 &GetLocalAnchorB(void) const
	{
		return m_LocalAnchorB;
	}

	void SetLength(float32 Value);
	float32 GetLength(void) const
	{
		return m_Length;
	}

	void SetDampingRatio(float32 Value);
	float32 GetDampingRatio(void) const
	{
		return m_DampingRatio;
	}

	void SetFrequency(float32 Value);
	float32 GetFrequency(void) const
	{
		return m_Frequency;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2DistanceJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;

	float m_Length;
	float m_DampingRatio;
	float m_Frequency;
};

END_NAMESPACE
#endif // DISTANCEJOINT_H
