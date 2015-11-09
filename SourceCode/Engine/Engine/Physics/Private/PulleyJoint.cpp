// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\PulleyJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


PulleyJoint::PulleyJoint(IPhysicsScene *Holder,
						 const String &Name,
						 IBody *BodyA,
						 IBody *BodyB,
						 bool CollideConnected,
						 const Vector2 &GroundAnchorA,
						 const Vector2 &LocalAnchorA,
						 const Vector2 &GroundAnchorB,
						 const Vector2 &LocalAnchorB,
						 const float LengthA,
						 const float LengthB,
						 const float Ratio) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_GroundAnchorA(GroundAnchorA),
	m_GroundAnchorB(GroundAnchorB),
	m_LengthA(LengthA),
	m_LengthB(LengthB),
	m_Ratio(Ratio)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	
	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_PULLEY;

	Prepare();
}


PulleyJoint::~PulleyJoint(void)
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


bool PulleyJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddVector2("GroundAnchorA", m_GroundAnchorA);
	Attributes->AddVector2("GroundAnchorB", m_GroundAnchorB);
	Attributes->AddFloat("LengthA", m_LengthA);
	Attributes->AddFloat("LengthB", m_LengthB);
	Attributes->AddFloat("Ratio", m_Ratio);

	return true;
}


bool PulleyJoint::Deserialize(IAttributes *Attributes)
{
	return true;
}


const Vector2 PulleyJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}


const Vector2 PulleyJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}


void PulleyJoint::Prepare(void)
{
	b2PulleyJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.collideConnected = m_CollideConnected;
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);
	jointDef.groundAnchorA.Set(m_GroundAnchorA.X, m_GroundAnchorA.Y);
	jointDef.groundAnchorB.Set(m_GroundAnchorB.X, m_GroundAnchorB.Y);
	jointDef.lengthA = m_LengthA;
	jointDef.lengthB = m_LengthB;
	jointDef.ratio = m_Ratio;

	m_Joint = static_cast<b2PulleyJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
