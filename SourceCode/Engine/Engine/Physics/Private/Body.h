// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BODY_H
#define BODY_H

#include <Public\Physics\IBody.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class Body : public IBody
{
public:
	Body(IGameObject *GameObject, IPhysicsScene *Scene);

	virtual ~Body(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	IPhysicsScene *GetSceneHolder(void) const;
	IGameObject *GetHolder(void) const;

	void SetTransform(const Vector2 &Position, float32 Rotation);
	void SetPosition(const Vector2 &Position);
	void SetRotation(float32 Rotation);

	const Vector2 &GetPosition(void) const
	{
		return m_Position;
	}

	float32 GetAngle(void) const
	{
		return m_Body->GetAngle();
	}

	void SetLinearDamping(float32 Value);
	float32 GetLinearDamping(void) const
	{
		return m_LinearDamping;
	}

	void SetAngularDamping(float32 Value);
	float32 GetAngularDamping(void) const
	{
		return m_AngularDamping;
	}

	void SetLinearVelocity(const Vector2 &velocity);
	const Vector2 &GetLinearVelocity(void) const
	{
		return m_LinearVelocity;
	}

	void SetAngularVelocity(float32 Value);
	float32 GetAngularVelocity(void) const
	{
		return m_AngularVelocity;
	}

	void SetGravityScale(float32 Value);
	float32 GetGravityScale(void) const
	{
		return m_GravityScale;
	}

	void SetSleepingAllowed(bool Flag)
	{
		m_Body->SetSleepingAllowed(Flag);
	}
	const bool IsSleepingAllowed(void) const
	{
		return m_Body->IsSleepingAllowed();
	}

	void SetAwake(bool Flag)
	{
		m_Body->SetAwake(Flag);
	}
	const bool IsAwake(void) const
	{
		return m_Body->IsAwake();
	}

	void SetUseCCD(bool Flag);
	bool IsUsingCCD(void) const
	{
		return m_IsUsingCCD;
	}

	void SetActive(bool Flag);
	bool IsActive(void) const
	{
		return m_Active;
	}

	void SetType(const BodyType &Type);
	const BodyType &GetType(void) const
	{
		return m_Type;
	}

	const Vector2 GetWorldCenterOfMass(void) const;
	const Vector2 GetLocalCenterOfMass(void) const;

	void ApplyForce(const Vector2 &force, const Vector2 &point);

	void ApplyLinearImpulse(const Vector2 &force, const Vector2 &point);

	void ApplyTorque(float32 Value)
	{
		m_Body->ApplyTorque(Value);
	}

	void ApplyAngularImpulse(float32 Value)
	{
		m_Body->ApplyAngularImpulse(Value);
	}

#ifndef LAUNCE_MODE
	void AddFixture(IFixture *Fixture);
	void RemoveFixture(IFixture *_Fixture);
#endif
	IFixture *CreateFixture(const String &Name);
	void DestroyFixture(const String &Name);
	void DestroyFixture(IFixture *Fixture);

	IFixture *Body::GetFixture(int32 Index)
	{
		return m_FixturesList[Index];
	}
	IFixture *GetFixture(const String &Name);
	FixturesList &GetFixtures(void)
	{
		return m_FixturesList;
	}

	const unsigned int GetFixturesCount(void) const
	{
		return m_FixturesList.GetSize();
	}

	void Body::SetContact(IContact *Contact)
	{
		m_Contact = Contact;
	}
	IContact *Body::GetContact(void) const
	{
		return m_Contact;
	}

	const bool IsShapeConvex(const List<Vector2> &Vertices);

	b2Body *GetBox2DBody(void)
	{
		return m_Body;
	}

private:
	IPhysicsScene *m_SceneHolder;
	b2Body *m_Body;

	IGameObject *m_Holder;

	FixturesList m_FixturesList;
	

	IContact *m_Contact;

	Vector2 m_Position;
	BodyType m_Type;
	float32 m_LinearDamping;
	float32 m_AngularDamping;
	float32 m_AngularVelocity;
	Vector2 m_LinearVelocity;
	bool m_Active;
	float32 m_GravityScale;
	bool m_IsUsingCCD;
};

END_NAMESPACE
#endif // BODY_H
