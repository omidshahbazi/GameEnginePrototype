// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\WheelJoint.h>
#include <Private\PhysicsCommon.h>
#include <Private\PhysicsScene.h>
#include <Private\Body.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


WheelJoint::WheelJoint(IPhysicsScene *Holder,
					   const String &Name,
					   IBody *BodyA,
					   IBody *BodyB,
					   bool CollideConnected,
					   const Vector2 &LocalAxisA,
					   const Vector2 &LocalAnchorA,
					   const Vector2 &LocalAnchorB) :
	m_LocalAnchorA(LocalAnchorA),
	m_LocalAnchorB(LocalAnchorB),
	m_LocalAxisA(LocalAxisA),
	m_IsMotorEnabled(false),
	m_MotorSpeed(0.f),
	m_MaxMotorTorque(0.f),
	m_SpringFrequencyHz(0.f),
	m_SpringDampingRatio(0.f)
{
	BREAK_PROCESS_IF(!m_BodyA);
	BREAK_PROCESS_IF(!m_BodyB);

	m_Holder = Holder;
	m_Name = Name;
	m_BodyA = BodyA;
	m_BodyB = BodyB;
	m_CollideConnected = CollideConnected;
	m_Type = JT_WHEEL;

	Prepare();
}


WheelJoint::~WheelJoint(void)
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


bool WheelJoint::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddInteger("Type", m_Type);
	Attributes->AddString("BodyA", m_BodyA->GetHolder()->GetName());
	Attributes->AddString("BodyB", m_BodyB->GetHolder()->GetName());
	Attributes->AddBoolean("Collided", m_CollideConnected);
	Attributes->AddVector2("LocalAxisA", m_LocalAxisA);
	Attributes->AddVector2("LocalAnchorA", m_LocalAnchorA);
	Attributes->AddVector2("LocalAnchorB", m_LocalAnchorB);
	Attributes->AddFloat("MaxMotorTorque", m_MaxMotorTorque);
	Attributes->AddBoolean("IsMotorEnabled", m_IsMotorEnabled);
	Attributes->AddFloat("MotorSpeed", m_MotorSpeed);
	Attributes->AddFloat("Frequency", m_SpringFrequencyHz);
	Attributes->AddFloat("DampingRatio", m_SpringDampingRatio);

	return true;
}


bool WheelJoint::Deserialize(IAttributes *Attributes)
{
	EnableMotor(Attributes->GetBoolean("IsMotorEnabled"));
	SetMaxMotorTorque(Attributes->GetFloat("MaxMotorTorque"));
	SetMotorSpeed(Attributes->GetFloat("MotorSpeed"));
	SetSpringFrequencyHz(Attributes->GetFloat("Frequency"));
	SetSpringDampintRatio(Attributes->GetFloat("DampingRatio"));

	return true;
}


const Vector2 WheelJoint::GetAnchorA(void) const
{
	return ToVector2(m_Joint->GetAnchorA());
}


const Vector2 WheelJoint::GetAnchorB(void) const
{
	return ToVector2(m_Joint->GetAnchorB());
}


void WheelJoint::EnableMotor(bool Flag)
{
	m_IsMotorEnabled = Flag;
	m_Joint->EnableMotor(Flag);
}


void WheelJoint::SetMotorSpeed(float32 Value)
{
	m_MotorSpeed = Value;
	m_Joint->SetMotorSpeed(Value);
}


void WheelJoint::SetMaxMotorTorque(float32 Value)
{
	m_MaxMotorTorque = Value;
	m_Joint->SetMaxMotorTorque(Value);
}


void WheelJoint::SetSpringFrequencyHz(float32 Value)
{
	m_SpringFrequencyHz = Value;
	m_Joint->SetSpringFrequencyHz(Value);
}


void WheelJoint::SetSpringDampintRatio(float32 Value)
{
	m_SpringDampingRatio = Value;
	m_Joint->SetSpringDampingRatio(Value);
}


void WheelJoint::Prepare(void)
{
	b2WheelJointDef jointDef;
	jointDef.bodyA = ((Body*)m_BodyA)->GetBox2DBody();
	jointDef.bodyB = ((Body*)m_BodyB)->GetBox2DBody();
	jointDef.localAxisA.Set(m_LocalAxisA.X, m_LocalAxisA.Y);
	jointDef.localAnchorA.Set(m_LocalAnchorA.X, m_LocalAnchorA.Y);
	jointDef.localAnchorB.Set(m_LocalAnchorB.X, m_LocalAnchorB.Y);
	jointDef.collideConnected = m_CollideConnected;

	m_Joint = static_cast<b2WheelJoint*>(((PhysicsScene*)m_Holder)->CreateBox2DJoint(&jointDef));
}


END_NAMESPACE
