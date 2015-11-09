// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ROPEJOINT_H
#define ROPEJOINT_H

#include <Public\Physics\IRopeJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class RopeJoint : public IRopeJoint
{
public:
	RopeJoint(IPhysicsScene *Holder,
			  const String &Name,
			  IBody *BodyA,
			  IBody *BodyB,
		  	  bool CollideConnected = false,
			  const Vector2 &LocalAnchorA = Vector2(0, 0),
			  const Vector2 &LocalAnchorB = Vector2(0, 0));

	virtual ~RopeJoint(void);

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

	void SetMaxLength(float32 Value);
	float32 GetMaxLength(void) const
	{
		return m_MaxLength;
	}

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2RopeJoint *m_Joint;

	Vector2 m_LocalAnchorA;
	Vector2 m_LocalAnchorB;

	float m_MaxLength;
};

END_NAMESPACE
#endif // ROPEJOINT_H
