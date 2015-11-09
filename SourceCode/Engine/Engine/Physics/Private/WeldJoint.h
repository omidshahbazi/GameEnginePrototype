// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef WELDJOINT_H
#define WELDJOINT_H

#include <Public\Physics\IWeldJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class WeldJoint : public IWeldJoint
{
public:
	WeldJoint(IPhysicsScene *Holder,
			   const String &Name,
			   IBody *BodyA,
			   IBody *BodyB,
			   bool CollideConnected = false,
			   const Vector2 &LocalAnchorA = Vector2(-1, 0),
			   const Vector2 &LocalAnchorB = Vector2(1, 0),
			   float32 ReferenceAngle = 0);

	virtual ~WeldJoint(void);

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


	float32 GetReferenceAngle(void) const
	{
		return m_ReferenceAngle;
	}

	void SetFrequencyHz(float32 Value);
	float32 GetFrequencyHz(void) const
	{
		return m_FrequencyHz;
	}

	void SetDampintRatio(float32 Value);
	float32 GetDampingRatio(void) const
	{
		return m_DampingRatio;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2WeldJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;

	float m_ReferenceAngle;
	float m_FrequencyHz;
	float m_DampingRatio;
};

END_NAMESPACE
#endif // WELDJOINT_H
