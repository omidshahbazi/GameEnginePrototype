// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\PrismaticJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>
#include <Public\CMath.h>


BEGIN_NAMESPACE


PrismaticJoint::PrismaticJoint(IPhysicsScene *Holder,
							   const String &Name,
							   IBody *BodyA,
							   IBody *BodyB,
							   bool CollideConnected,
							   const Vector2 &LocalAxisA,
							   const Vector2 &LocalAnchorA,
							   const Vector2 &LocalAnchorB,
							   const float ReferenceAngle) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_ReferenceAngle(ReferenceAngle),
	m_IsLimitEnabled(false),
	m_IsMotorEnabled(false),
	m_UpperLimit(0.f),
	m_LowerLimit(0.f),
	m_MotorSpeed(0.f),
	m_MaxMotorForce(0.f)

{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_PRISMATIC;

	Prepare();
}


PrismaticJoint::~PrismaticJoint(void)
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


bool PrismaticJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAxisA", ToVector2(m_Joint->GetLocalAxisA()));
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddFloat("ReferenceAngle", m_ReferenceAngle);
	Attributes->AddBoolean("IsMotorEnabled", m_IsMotorEnabled);
	Attributes->AddBoolean("IsLimited", m_IsLimitEnabled);
	Attributes->AddFloat("LowerLimit", m_LowerLimit);
	Attributes->AddFloat("UpperLimit", m_UpperLimit);
	Attributes->AddFloat("MotorSpeed", m_MotorSpeed);
	Attributes->AddFloat("MaxMotorForce", m_MaxMotorForce);

	return true;
}


bool PrismaticJoint::Deserialize(IAttributes *Attributes)
{
	EnableMotor(Attributes->GetBoolean("IsMotorEnabled"));
	EnableLimit(Attributes->GetBoolean("IsLimited"));
	SetLimits(Attributes->GetFloat("LowerLimit"), Attributes->GetFloat("UpperLimit"));
	SetMotorSpeed(Attributes->GetFloat("MotorSpeed"));
	SetMaxMotorForce(Attributes->GetFloat("MaxMotorForce"));

	return true;
}


const Vector2 PrismaticJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}


const Vector2 PrismaticJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}


void PrismaticJoint::EnableLimit(bool Flag)
{
	m_IsLimitEnabled = Flag;
	m_Joint->EnableLimit(Flag);
}


void PrismaticJoint::SetLimits(float32 LowerAngle, float32 UpperAngle)
{
	m_LowerLimit = LowerAngle;
	m_UpperLimit = UpperAngle;
	m_Joint->SetLimits(LowerAngle * Math::DEGREES_TO_RADIANS, UpperAngle * Math::DEGREES_TO_RADIANS);
}


void PrismaticJoint::SetLowerLimit(float32 Value)
{
	m_LowerLimit = Value;
	m_Joint->SetLimits(Value * Math::DEGREES_TO_RADIANS, m_Joint->GetUpperLimit());
}


void PrismaticJoint::SetUpperLimit(float32 Value)
{
	m_UpperLimit = Value;
	m_Joint->SetLimits(m_Joint->GetLowerLimit(), Value * Math::DEGREES_TO_RADIANS);
}


void PrismaticJoint::EnableMotor(bool Flag)
{
	m_IsMotorEnabled = Flag;
	m_Joint->EnableMotor(Flag);
}


void PrismaticJoint::SetMotorSpeed(float32 Value)
{
	m_MotorSpeed = Value;
	m_Joint->SetMotorSpeed(Value);
}


void PrismaticJoint::SetMaxMotorForce(float32 Value)
{
	m_MaxMotorForce = Value;
	m_Joint->SetMaxMotorForce(Value);
}

const float PrismaticJoint::GetMotorForce(float32 InverseDeltaTime) const
{
	return m_Joint->GetMotorForce(InverseDeltaTime);
}


b2PrismaticJoint *PrismaticJoint::GetBox2DJopint(void)
{
	return m_Joint;
}


void PrismaticJoint::Prepare(void)
{
	b2PrismaticJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.collideConnected = m_CollideConnected;
	jointDef.localAxisA.Set(m_LocalAxisA.X, m_LocalAxisA.Y);
	jointDef.localAxisA.Normalize();
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);
	jointDef.referenceAngle = m_ReferenceAngle;

	m_Joint = static_cast<b2PrismaticJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
