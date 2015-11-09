// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPHYSICSSCENE_H
#define IPHYSICSSCENE_H

#include <Public\Common.h>
#include <Public\ISerializable.h>
#include <Public\IBaseObject.h>

BEGIN_NAMESPACE

class IBody;
class IJoint;
class IPrismaticJoint;
class IRevoluteJoint;
class IGameObject;
struct Vector2;

class IPhysicsScene : public ISerializable
{
public:
	typedef Vector<IJoint*> JointList;

public:
	virtual ~IPhysicsScene(void) {}

	virtual void SetGravity(const Vector2 &Gravity) = 0;
	virtual const Vector2 &GetGravity(void) const = 0;

	virtual void Update(void) = 0;

	virtual IBody *CreateBody(IGameObject *GameObject) = 0;
	virtual void DestroyBody(IBody *Body) = 0;

	virtual void SetAllowSleeping(bool Flag) = 0;
	virtual bool GetAllowSleeping(void) const = 0;

	virtual IJoint *CreateRevoluteJoint(const String &Name,
										IBody *BodyA,
										IBody *BodyB,
										bool CollideConnected,
										const Vector2 &LocalAnchorA,
										const Vector2 &LocalAnchorB,
										float ReferenceAngle) = 0;

	virtual IJoint *CreatePrismaticJoint(const String &Name,
										 IBody *BodyA,
										 IBody *BodyB,
										 bool CollideConnected,
										 const Vector2 &LocalAxisA,
										 const Vector2 &LocalAnchorA,
										 const Vector2 &LocalAnchorB,
										 float ReferenceAngle) = 0;

	virtual IJoint *CreateDistanceJoint(const String &Name,
										IBody *BodyA,
										IBody *BodyB,
										bool CollideConnected,
										const Vector2 &LocalAnchorA,
										const Vector2 &LocalAnchorB) = 0;

	virtual IJoint *CreateRopeJoint(const String &Name,
									IBody *BodyA,
									IBody *BodyB,
									bool CollideConnected,
									const Vector2 &LocalAnchorA,
									const Vector2 &LocalAnchorB) = 0;

	virtual IJoint *CreatePulleyJoint(const String &Name,
									  IBody *BodyA,
									  IBody *BodyB,
									  bool CollideConnected,
									  const Vector2 &GroundAnchorA,
									  const Vector2 &LocalAnchorA,
									  const Vector2 &GroundAnchorB,
									  const Vector2 &LocalAnchorB,
									  const float LengthA,
									  const float LengthB,
									  const float Ratio) = 0;

	virtual IJoint *CreateGearJoint(const String &Name,
									IBody *BodyA,
									IBody *BodyB,
									bool CollideConnected,
									IRevoluteJoint *RevoluteJoint,
									IPrismaticJoint *PrismaticJoint) = 0;

	virtual IJoint *CreateWheelJoint(const String &Name,
									 IBody *BodyA,
									 IBody *BodyB,
									 bool CollideConnected,
								 	 const Vector2 &LocalAxisA,
									 const Vector2 &LocalAnchorA,
									 const Vector2 &LocalAnchorB) = 0;

	virtual IJoint *CreateWeldJoint(const String &Name,
									IBody *BodyA,
									IBody *BodyB,
									bool CollideConnected,
									const Vector2 &LocalAnchorA,
									const Vector2 &LocalAnchorB,
									float ReferenceAngle) = 0;

#ifndef LAUNCE_MODE
	virtual void AddJoint(IJoint *Joint) = 0;
	virtual void RemoveJoint(IJoint *Joint) = 0;
#endif
	virtual void DestroyJoint(IJoint *Joint) = 0;
	virtual IJoint *GetJoint(const String &Name) = 0;
	virtual JointList &GetJoints(void) = 0;
};

END_NAMESPACE
#endif // IPHYSICSSCENE_H
