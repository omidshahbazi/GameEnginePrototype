// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\WeldJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


WeldJoint::WeldJoint(IPhysicsScene *Holder,
					   const String &Name,
					   IBody *BodyA,
					   IBody *BodyB,
					   bool CollideConnected,
					   const Vector2 &LocalAnchorA,
					   const Vector2 &LocalAnchorB,
					   float32 ReferenceAngle) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_ReferenceAngle(ReferenceAngle),
	m_FrequencyHz(0.f),
	m_DampingRatio(0.f)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_WELD;

	Prepare();
}


WeldJoint::~WeldJoint(void)
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


bool WeldJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddFloat("ReferenceAngle", m_ReferenceAngle);
	Attributes->AddFloat("Frequency", m_FrequencyHz);
	Attributes->AddFloat("DampingRatio", m_DampingRatio);

	return true;
}


bool WeldJoint::Deserialize(IAttributes *Attributes)
{
	SetFrequencyHz(Attributes->GetFloat("Frequency"));
	SetDampintRatio(Attributes->GetFloat("DampingRatio"));

	return true;
}


const Vector2 WeldJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}


const Vector2 WeldJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}


void WeldJoint::SetFrequencyHz(float32 Value)
{
	m_FrequencyHz = Value;
	m_Joint->SetFrequency(Value);
}


void WeldJoint::SetDampintRatio(float32 Value)
{
	m_DampingRatio = Value;
	m_Joint->SetDampingRatio(Value);
}


void WeldJoint::Prepare(void)
{
	b2WeldJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);
	jointDef.collideConnected = m_CollideConnected;
	jointDef.referenceAngle = m_ReferenceAngle;

	m_Joint = static_cast<b2WeldJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
