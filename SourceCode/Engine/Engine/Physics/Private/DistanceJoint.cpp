// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\DistanceJoint.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


DistanceJoint::DistanceJoint(IPhysicsScene *Holder,
							 const String &Name,
							 IBody *BodyA,
							 IBody *BodyB,
							 bool CollideConnected,
							 const Vector2 &LocalAnchorA,
							 const Vector2 &LocalAnchorB) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_Length(0.f),
	m_DampingRatio(0.f),
	m_Frequency(0.f)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_DISTANCE;

	Prepare();
}


DistanceJoint::~DistanceJoint(void)
{
#ifndef LAUNCH_MODE
	if (m_Joint)
	{
#endif
	((PhysicsScene*)m_Holder)->DestroyBox2DJoint(m_Joint);
	m_Joint = NULL;
#ifndef LAUNCH_MODE
	}
#endif
}


bool DistanceJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddFloat("Length", m_Length);
	Attributes->AddFloat("DampintRatio", m_DampingRatio);
	Attributes->AddFloat("Frequency", m_Frequency);

	return true;
}


bool DistanceJoint::Deserialize(IAttributes *Attributes)
{
	SetLength(Attributes->GetFloat("Length"));
	SetDampingRatio(Attributes->GetFloat("DampintRatio"));
	SetFrequency(Attributes->GetBoolean("Frequency"));

	return true;
}


void DistanceJoint::SetLength(float32 Value)
{
	m_Length = Value;
	m_Joint->SetLength(Value);
}


void DistanceJoint::SetDampingRatio(float32 Value)
{
	m_DampingRatio = Value;
	m_Joint->SetDampingRatio(Value);
}


void DistanceJoint::SetFrequency(float32 Value)
{
	m_Frequency = Value;
	m_Joint->SetFrequency(Value);
}


void DistanceJoint::Prepare(void)
{
	b2DistanceJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.collideConnected = m_CollideConnected;
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);

	m_Joint = static_cast<b2DistanceJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
