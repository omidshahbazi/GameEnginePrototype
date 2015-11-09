// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GEARJOINT_H
#define GEARJOINT_H

#include <Public\Physics\IGearJoint.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class GearJoint : public IGearJoint
{
public:
	GearJoint(IPhysicsScene *Holder,
			  const String &Name,
			  IBody *BodyA,
			  IBody *BodyB,
			  bool CollideConnected = false,
			  IRevoluteJoint *RevoluteJoint = NULL,
			  IPrismaticJoint *PrismaticJoint = NULL);

	virtual ~GearJoint(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	const Vector2 GetAnchorA(void) const;

	const Vector2 GetAnchorB(void) const;

	void SetRatio(float32 Value);
	float32 GetRatio(void) const
	{
		return m_Ratio;
	}


	IRevoluteJoint *GetRevoluteJoint(void);
	IPrismaticJoint *GetPrismaticJoint(void);

	void *GetData(void)
	{
		return m_Joint;
	}

	void Prepare(void);

private:
	b2GearJoint *m_Joint;

	IRevoluteJoint *m_Revolute;
	IPrismaticJoint *m_Prismatic;

	float m_Ratio;

};

END_NAMESPACE
#endif // GEARJOINT_H
