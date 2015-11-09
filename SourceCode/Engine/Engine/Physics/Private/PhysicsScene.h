// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PHYSICSSCENE_H
#define PHYSICSSCENE_H

#include <Public\Physics\IPhysicsScene.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class ContactListener;

class PhysicsScene : public IPhysicsScene
{
public:
	PhysicsScene(void);
	virtual ~PhysicsScene(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	void SetGravity(const Vector2 &Gravity);
	const Vector2 &GetGravity(void) const
	{
		return m_Gravity;
	}

	void SetAllowSleeping(bool Flag);
	bool GetAllowSleeping(void) const
	{
		return m_AllowSleeping;
	}

	void Update(void);

	b2Body *CreateBox2DBody(const b2BodyDef *Def)
	{
		return m_World->CreateBody(Def);
	}
	void DestroyBox2DBody(b2Body *Body)
	{
		m_World->DestroyBody(Body);
	}

	b2Joint *CreateBox2DJoint(const b2JointDef *Def)
	{
		return m_World->CreateJoint(Def);
	}
	void DestroyBox2DJoint(b2Joint *Joint)
	{
		m_World->DestroyJoint(Joint);
	}

	IBody *CreateBody(IGameObject *GameObject);
	void DestroyBody(IBody *Body);

	IJoint *CreateRevoluteJoint(const String &Name,
								IBody *BodyA,
								IBody *BodyB,
								bool CollideConnected,
								const Vector2 &LocalAnchorA,
								const Vector2 &LocalAnchorB,
								float32 ReferenceAngle);

	IJoint *CreatePrismaticJoint(const String &Name,
								 IBody *BodyA,
								 IBody *BodyB,
								 bool CollideConnected,
								 const Vector2 &LocalAxisA,
								 const Vector2 &LocalAnchorA,
								 const Vector2 &LocalAnchorB,
								 float32 ReferenceAngle);

	IJoint *CreateDistanceJoint(const String &Name,
								IBody *BodyA,
								IBody *BodyB,
								bool CollideConnected,
								const Vector2 &LocalAnchorA,
								const Vector2 &LocalAnchorB);

	IJoint *CreateRopeJoint(const String &Name,
							IBody *BodyA,
							IBody *BodyB,
							bool CollideConnected,
							const Vector2 &LocalAnchorA,
							const Vector2 &LocalAnchorB);

	IJoint *CreatePulleyJoint(const String &Name,
							  IBody *BodyA,
							  IBody *BodyB,
						   	  bool CollideConnected,
							  const Vector2 &GroundAnchorA,
							  const Vector2 &LocalAnchorA,
							  const Vector2 &GroundAnchorB,
							  const Vector2 &LocalAnchorB,
							  const float LengthA = 0,
							  const float LengthB = 0,
							  const float Ratio = 1.0f);

	IJoint *CreateGearJoint(const String &Name,
							IBody *BodyA,
							IBody *BodyB,
						  	bool CollideConnected,
							IRevoluteJoint *RevoluteJoint = NULL,
							IPrismaticJoint *PrismaticJoint = NULL);

	IJoint *CreateWheelJoint(const String &Name,
							 IBody *BodyA,
							 IBody *BodyB,
							 bool CollideConnected,
							 const Vector2 &LocalAxisA,
							 const Vector2 &LocalAnchorA,
							 const Vector2 &LocalAnchorB);

	IJoint *CreateWeldJoint(const String &Name,
							IBody *BodyA,
							IBody *BodyB,
							bool CollideConnected,
							const Vector2 &LocalAnchorA,
							const Vector2 &LocalAnchorB,
							float32 ReferenceAngle);


#ifndef LAUNCE_MODE
	void AddJoint(IJoint *Joint);
	void RemoveJoint(IJoint *Joint);
#endif

	void DestroyJoint(IJoint *Joint);
	IJoint *GetJoint(const String &Name);
	JointList &GetJoints(void)
	{
		return m_JointsList;
	}

	b2World *GetBox2DWorld(void)
	{
		return m_World;
	}

private:
	b2World *m_World;

	Vector2 m_Gravity;
	bool m_AllowSleeping;

	const int VelocityIterations;
	const int PositionIterations;
	float m_TimeStep;

	JointList m_JointsList;

	ContactListener *m_ContactListener;
};

END_NAMESPACE
#endif // PHYSICSSCENE_H
