// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\RopeJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


RopeJoint::RopeJoint(IPhysicsScene *Holder,
					 const String &Name,
					 IBody *BodyA,
					 IBody *BodyB,
					 bool CollideConnected,
					 const Vector2 &LocalAnchorA,
					 const Vector2 &LocalAnchorB) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_MaxLength(0.f)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_ROPE;

	Prepare();
}


RopeJoint::~RopeJoint(void)
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


bool RopeJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", JT_ROPE);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddFloat("MaxLength", m_MaxLength);

	return true;
}


bool RopeJoint::Deserialize(IAttributes *Attributes)
{
	SetMaxLength(Attributes->GetFloat("MaxLength"));

	return true;
}


const Vector2 RopeJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}



const Vector2 RopeJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}



void RopeJoint::SetMaxLength(float32 Value)
{
	m_MaxLength = Value;
	m_Joint->SetMaxLength(Value);
}


void RopeJoint::Prepare(void)
{
	b2RopeJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.collideConnected = m_CollideConnected;
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);

	m_Joint = static_cast<b2RopeJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
