// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PULLEYJOINT_H
#define PULLEYJOINT_H

#include <Public\Physics\IPulleyJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class PulleyJoint : public IPulleyJoint
{
public:
	PulleyJoint(IPhysicsScene *Holder,
				const String &Name,
				IBody *BodyA,
				IBody *BodyB,
				bool CollideConnected = false,
				const Vector2 &GroundAnchorA = Vector2(-1, 1),
				const Vector2 &LocalAnchorA = Vector2(-1, 0),
				const Vector2 &GroundAnchorB = Vector2(1, 1),
				const Vector2 &LocalAnchorB = Vector2(1, 0),
				const float LengthA = 0,
				const float LengthB = 0,
				const float Ratio = 1.0f);

	virtual ~PulleyJoint(void);

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

	const Vector2 &GetGroundAnchorA(void) const
	{
		return m_GroundAnchorA;
	}

	const Vector2 &GetGroundAnchorB(void) const
	{
		return m_GroundAnchorB;
	}

	float32 GetLengthA(void) const
	{
		return m_LengthA;
	}

	float32 GetLenghtB(void) const
	{
		return m_LengthB;
	}

	float32 GetRatio(void) const
	{
		return m_Ratio;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2PulleyJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;
	Vector2 m_GroundAnchorA;
	Vector2 m_GroundAnchorB;

	float m_LengthA;
	float m_LengthB;
	float m_Ratio;
};

END_NAMESPACE
#endif // PULLEYJOINT_H
