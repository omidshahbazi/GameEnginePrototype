// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IBODY_H
#define IBODY_H

#include <Public\ISerializable.h>
#include <Public\IBaseObject.h>

BEGIN_NAMESPACE

class IPhysicsScene;
class IFixture;
class IContact;
class IContactImpulse;
class IGameObject;

class IBody : public ISerializable
{
public:
	enum class BodyType
	{
		BT_STATIC = 0,
		BT_KINEMATIC,
		BT_DYNAMIC
	};

public:
	typedef Vector<IFixture*> FixturesList;

public:
	virtual ~IBody(void) {}

	virtual IPhysicsScene *GetSceneHolder(void) const = 0;
	virtual IGameObject *GetHolder(void) const = 0;


	virtual void SetTransform(const Vector2 &Position, float32 Rotation) = 0;
	virtual void SetPosition(const Vector2 &Position) = 0;
	virtual void SetRotation(float32 Rotation) = 0;

	virtual const Vector2 &GetPosition(void) const = 0;

	virtual float32 GetAngle(void) const = 0;

	virtual void SetLinearDamping(float32 Value) = 0;
	virtual float32 GetLinearDamping(void) const = 0;

	virtual void SetAngularDamping(float32 Value) = 0;
	virtual float32 GetAngularDamping(void) const = 0;

	virtual void SetLinearVelocity(const Vector2 &Velocity) = 0;
	virtual const Vector2 &GetLinearVelocity(void) const = 0;

	virtual void SetAngularVelocity(float32 Value) = 0;
	virtual float32 GetAngularVelocity(void) const = 0;

	virtual void SetGravityScale(float32 Value) = 0;
	virtual float32 GetGravityScale(void) const = 0;

	virtual void SetSleepingAllowed(bool Flag) = 0;
	virtual const bool IsSleepingAllowed(void) const = 0;

	virtual void SetAwake(bool Flag) = 0;
	virtual const bool IsAwake(void) const = 0;

	virtual void SetUseCCD(bool Flag) = 0;
	virtual bool IsUsingCCD(void) const = 0;

	virtual void SetActive(bool Flag) = 0;
	virtual bool IsActive(void) const = 0;

	virtual void SetType(const BodyType &Type) = 0;
	virtual const BodyType &GetType(void) const = 0;

	virtual const Vector2 GetWorldCenterOfMass(void) const = 0;
	virtual const Vector2 GetLocalCenterOfMass(void) const = 0;

	virtual void ApplyForce(const Vector2 &Force, const Vector2 &Point) = 0;
	virtual void ApplyLinearImpulse(const Vector2 &Force, const Vector2 &Point) = 0;
	virtual void ApplyTorque(float32 Value) = 0;
	virtual void ApplyAngularImpulse(float32 Value) = 0;

#ifndef LAUNCE_MODE
	virtual void AddFixture(IFixture *Fixture) = 0;
	virtual void RemoveFixture(IFixture *Fixture) = 0;
#endif
	virtual IFixture *CreateFixture(const String &Name) = 0;
	virtual void DestroyFixture(const String &Name) = 0;
	virtual void DestroyFixture(IFixture *Fixture) = 0;

	virtual IFixture *GetFixture(int32 Index) = 0;
	virtual IFixture *GetFixture(const String &Name) = 0;
	virtual FixturesList &GetFixtures(void)= 0;
	virtual const uint32 GetFixturesCount(void) const = 0;

	virtual void SetContact(IContact *Contact) = 0;
	virtual IContact *GetContact(void) const = 0;
	
	virtual const bool IsShapeConvex(const List<Vector2> &Vertices) = 0;
};

END_NAMESPACE
#endif // IBODY_H
