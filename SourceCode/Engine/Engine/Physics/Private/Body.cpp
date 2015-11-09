// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Body.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Fixture.h>
#include <Public\Physics\IJoint.h>
#include <Public\Physics\IContact.h>
#include <Public\IGameObject.h>
#include "ITransform.h"
#include <Public\CMath.h>


BEGIN_NAMESPACE


Body::Body(IGameObject *GameObject, IPhysicsScene *Scene) :
	m_SceneHolder(Scene),
	m_Position(Vector2()),
	m_Type(BodyType::BT_STATIC),
	m_Contact(NULL),
	m_Active(true),
	m_LinearDamping(0.05f),
	m_AngularDamping(0.f),
	m_LinearVelocity(Vector2(0,0)),
	m_AngularVelocity(0.f),
	m_GravityScale(1.f),
	m_IsUsingCCD(false)
{
	b2BodyDef bodyDef;

	USE_BREAK_PROCESS_IF(!GameObject);

	m_Position = Vector2(GameObject->GetTransform()->GetPosition().X, GameObject->GetTransform()->GetPosition().Y);
	bodyDef.position.Set(m_Position.X, m_Position.Y);
	bodyDef.angle = GameObject->GetTransform()->GetRotation().Z * Math::DEGREES_TO_RADIANS;
	m_Holder = GameObject;
	
	m_Body = static_cast<PhysicsScene*>(m_SceneHolder)->CreateBox2DBody(&bodyDef);
	m_Body->SetUserData(this);
}


Body::~Body(void)
{
#ifndef LAUNCH_MODE
	if (m_Holder)
	{
#endif
		FOR_EACH(fixture, m_FixturesList)
			delete &fixture;

		((PhysicsScene*)m_SceneHolder)->DestroyBox2DBody(m_Body);
#ifndef LAUNCH_MODE
	}
#endif
	
	LOG_INFO_DEBUG("IBody of [" + m_Holder->GetName() + "] destoryed successfully")
}


bool Body::Serialize(IAttributes *Attributes)
{
	Attributes->AddVector2("Position", ToVector2(m_Body->GetPosition()));
	Attributes->AddFloat("Rotation", m_Body->GetAngle() * Math::RADIANS_TO_DEGREES);
	Attributes->AddFloat("LinearDamping", m_Body->GetLinearDamping());
	Attributes->AddFloat("AngularDamping", m_Body->GetAngularDamping());
	Attributes->AddFloat("GravityScale", m_Body->GetGravityScale());
	Attributes->AddBoolean("SleepingAllows", m_Body->IsSleepingAllowed());
	Attributes->AddBoolean("Awake", m_Body->IsAwake());
	Attributes->AddBoolean("UseCCD", m_Body->IsBullet());
	Attributes->AddBoolean("Active", m_Body->IsActive());
	Attributes->AddInteger("Type", m_Body->GetType());
	Attributes->AddVector2("LinearVelocity", ToVector2(m_Body->GetLinearVelocity()));
	Attributes->AddFloat("AngularVelocity", m_Body->GetAngularVelocity());

	return true;
}


bool Body::Deserialize(IAttributes *Attributes)
{
	SetTransform(Attributes->GetVector2("Position"), Attributes->GetFloat("Rotation"));
	SetLinearDamping(Attributes->GetFloat("LinearDamping"));
	SetAngularDamping(Attributes->GetFloat("AngularDamping"));
	SetGravityScale(Attributes->GetFloat("GravityScale"));
	SetSleepingAllowed(Attributes->GetBoolean("SleepingAllows"));
	SetAwake(Attributes->GetBoolean("Awake"));
	SetUseCCD(Attributes->GetBoolean("UseCCD"));
	SetActive(Attributes->GetBoolean("Active"));
	SetType((IBody::BodyType)Attributes->GetInteger("Type"));
	SetLinearVelocity(Attributes->GetVector2("LinearVelocity"));
	SetAngularVelocity(Attributes->GetFloat("AngularVelocity"));

	return true;
}


IPhysicsScene *Body::GetSceneHolder(void) const
{
	return m_SceneHolder;
}


IGameObject *Body::GetHolder(void) const
{
	return m_Holder;
}


void Body::SetTransform(const Vector2 &Position, float32 Rotation)
{
	m_Position = Position;
	m_Body->SetTransform(Tob2Vec2(m_Position), Rotation * Math::DEGREES_TO_RADIANS);
}


void Body::SetPosition(const Vector2 &Position)
{
	m_Position = Position;
	m_Body->SetTransform(Tob2Vec2(m_Position), m_Body->GetAngle());
}


void Body::SetRotation(float32 Rotation)
{
	m_Body->SetTransform(m_Body->GetPosition(), Rotation * Math::DEGREES_TO_RADIANS);
}


void Body::SetLinearDamping(float32 Value)
{
	m_LinearDamping = Value;
	m_Body->SetLinearDamping(Value);
}


void Body::SetAngularDamping(float32 Value)
{
	m_AngularDamping = Value;
	m_Body->SetAngularDamping(Value);
}


void Body::SetLinearVelocity(const Vector2 &Velocity)
{
	m_LinearVelocity = Velocity;
	m_Body->SetLinearVelocity(Tob2Vec2(Velocity));
}


void Body::SetAngularVelocity(float32 Value)
{
	m_AngularVelocity = Value;
	m_Body->SetAngularVelocity(Value);
}


void Body::SetGravityScale(float32 Value)
{
	m_GravityScale = Value;
	m_Body->SetGravityScale(Value);
}


void Body::SetUseCCD(bool Flag)
{
	m_IsUsingCCD = Flag;
	m_Body->SetBullet(Flag);
}


void Body::SetActive(bool Flag)
{
	m_Active = Flag;
	m_Body->SetActive(Flag);
}


void Body::SetType(const BodyType &Type)
{
	m_Type = Type;
	m_Body->SetType((b2BodyType)Type);
}


const Vector2 Body::GetWorldCenterOfMass(void) const
{
	return ToVector2(m_Body->GetWorldCenter());
}


const Vector2 Body::GetLocalCenterOfMass(void) const
{
	return ToVector2(m_Body->GetLocalCenter());
}


void Body::ApplyForce(const Vector2 &force, const Vector2 &point)
{
	m_Body->ApplyForce(Tob2Vec2(force), Tob2Vec2(point));
}


void Body::ApplyLinearImpulse(const Vector2 &force, const Vector2 &point)
{
	m_Body->ApplyLinearImpulse(Tob2Vec2(force), Tob2Vec2(point));
}


#ifndef LAUNCE_MODE
void Body::AddFixture(IFixture *Fixture)
{
	m_FixturesList.Add(Fixture);
	Fixture->Prepare(Fixture->GetShape());
}


void Body::RemoveFixture(IFixture *_Fixture)
{
	Fixture *fixture = static_cast<Fixture*>(_Fixture);
	m_Body->DestroyFixture(fixture->GetBox2DFixture());
	fixture->SetBox2DFixture(NULL);

	m_FixturesList.Remove(_Fixture);
}
#endif


IFixture *Body::CreateFixture(const String &Name)
{
	if (GetFixture(Name))
	{
		LOG_ERROR("Fixture with name [" + Name + "] already exists.")

		return NULL;
	}

	IFixture *fixture = new Fixture(m_Body, Name);

	m_FixturesList.Add(fixture);

	return fixture;
}


void Body::DestroyFixture(const String &Name)
{
	IFixture *fixture = GetFixture(Name);

	DestroyFixture(fixture);
}


void Body::DestroyFixture(IFixture *Fixture)
{
	if (Fixture)
	{
		m_FixturesList.Remove(Fixture);
		delete Fixture;
	}
}


IFixture *Body::GetFixture(const String &Name)
{
	FOR_EACH(f, m_FixturesList)
		if (f->GetName() == Name)
			return &f;

	return NULL;
}


const bool Body::IsShapeConvex(const List<Vector2> &Vertices)
{
	uint32 vertexCount = Vertices.GetSize();

	if (vertexCount <= 2)
		return false;

	b2Vec2 *verts = new b2Vec2[vertexCount];

	for (unsigned int i = 0; i < vertexCount; i++)
	{
		verts[i].Set(Vertices.operator[](i).X, Vertices[i].Y);

		unsigned int i1 = i;
		unsigned int i2 = i + 1 < vertexCount ? i + 1 : 0;

		// Ensure the polygon is convex and the interior
		// is to the left of each edge.
		b2Vec2 edge =  b2Vec2(Vertices[i2].X, Vertices[i2].Y) - verts[i1];

		for (unsigned int j = 0; j < vertexCount; ++j)
		{
			// Don't check vertices on the current edge.
			if (j == i1 || j == i2)
			{
				continue;
			}
				
			b2Vec2 r = b2Vec2(Vertices[j].X, Vertices[j].Y) - verts[i1];

			// If this crashes, your polygon is non-convex, has colinear edges,
			// or the winding order is wrong.
			if (b2Cross(edge, r) <= 0.f)
				return false;
		}
	}

	return true;
}


END_NAMESPACE
