// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GearJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Private\PrismaticJoint.h>
#include <Private\RevoluteJoint.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


GearJoint::GearJoint(IPhysicsScene *Holder,
					 const String &Name,
					 IBody *BodyA,
					 IBody *BodyB,
					 bool CollideConnected,
					 IRevoluteJoint *_RevoluteJoint,
					 IPrismaticJoint *P_rismaticJoint) :
	m_Revolute(_RevoluteJoint),
	m_Prismatic(P_rismaticJoint),
	m_Ratio(0.f)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_GEAR;

	Prepare();
}


GearJoint::~GearJoint(void)
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


bool GearJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddString("JointA", m_Revolute->GetName());
	Attributes->AddString("JointB", m_Prismatic->GetName());
	Attributes->AddBoolean("Collieded", m_Joint->GetCollideConnected());
	Attributes->AddFloat("Ratio", m_Ratio);

	return true;
}


bool GearJoint::Deserialize(IAttributes *Attributes)
{
	SetRatio(Attributes->GetFloat("Ratio"));

	return true;
}


const Vector2 GearJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}


const Vector2 GearJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}


void GearJoint::SetRatio(float32 Value)
{
	m_Ratio = Value;
	m_Joint->SetRatio(Value);
}


IRevoluteJoint *GearJoint::GetRevoluteJoint(void)
{
	return m_Revolute;
}


IPrismaticJoint *GearJoint::GetPrismaticJoint(void)
{
	return m_Prismatic;
}


void GearJoint::Prepare(void)
{
	b2GearJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.joint1 = ((RevoluteJoint*)m_Revolute)->GetBox2DJopint(); 
	jointDef.joint2 = ((PrismaticJoint*)m_Prismatic)->GetBox2DJopint(); 
	jointDef.collideConnected = m_CollideConnected;

	m_Joint = static_cast<b2GearJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
