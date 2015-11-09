// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\PhysicsScene.h>
#include <Private\PhysicsCommon.h>
#include <Private\Body.h>
#include <Private\ContactListener.h>
#include <Private\RevoluteJoint.h>
#include <Private\PrismaticJoint.h>
#include <Private\DistanceJoint.h>
#include <Private\RopeJoint.h>
#include <Private\PulleyJoint.h>
#include <Private\GearJoint.h>
#include <Private\WheelJoint.h>
#include <Private\WeldJoint.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>
#include <Public\CTime.h>
#include "ITransform.h"
#include <Public\CMath.h>


BEGIN_NAMESPACE


PhysicsScene::PhysicsScene(void) :
	VelocityIterations(8),
	PositionIterations(3),
	m_TimeStep(1.0f / 60.0f),
	m_AllowSleeping(false),
	m_Gravity(0, -9.8f)
{
	m_ContactListener = new ContactListener();

	m_World = new b2World(Tob2Vec2(m_Gravity));
	m_World->SetContactListener(m_ContactListener);
}


PhysicsScene::~PhysicsScene(void)
{
#ifndef LAUNCH_MODE
	if (m_World)
	{
#endif
		if (m_World->GetBodyCount() > 0)
			THROW_EXCEPTION_AND_RESUME(Exception::ER_PERFORMANCE_HIT, "Undestroyed bodies detected", "IPhysicsScene::~PhysicsScene")

		delete m_World;
		m_World = NULL;
#ifndef LAUNCH_MODE
	}
#endif

#ifndef LAUNCH_MODE
	if (m_ContactListener)
	{
#endif
		delete m_ContactListener;
		m_ContactListener = NULL;
#ifndef LAUNCH_MODE
	}
#endif


	LOG_INFO_DEBUG("IPhysicsScene destoryed successfully")
}


bool PhysicsScene::Serialize(IAttributes *Attributes)
{
	Attributes->AddVector2("Gravity", GetGravity());
	Attributes->AddBoolean("AllowSleeping", GetAllowSleeping());

	return true;
}


bool PhysicsScene::Deserialize(IAttributes *Attributes)
{
	SetGravity(Attributes->GetVector2("Gravity"));
	SetAllowSleeping(Attributes->GetBoolean("AllowSleeping"));

	return true;
} 


void PhysicsScene::SetGravity(const Vector2 &Gravity)
{
	m_Gravity = Gravity;
	m_World->SetGravity(Tob2Vec2(Gravity));
}


void PhysicsScene::SetAllowSleeping(bool Flag)
{
	m_AllowSleeping = Flag;
	m_World->SetAllowSleeping(Flag);
}


void PhysicsScene::Update(void)
{
	const float dt = (float)Time::GetReference().GetDeltaTime() / 1000.f;

	b2Body *node = NULL;
	IGameObject *object = NULL;

	node = m_World->GetBodyList();
	IBody *body = NULL;
	Vector2 vec2D;
	while (node)
	{
		body = static_cast<IBody*>(node->GetUserData());
		if (body)
		{
			object = body->GetHolder();

			const Vector3 &absPos = object->GetTransform()->GetPosition();

			vec2D.X = absPos.X;
			vec2D.Y = absPos.Y;

			body->SetAwake(true);
			body->SetTransform(vec2D, object->GetTransform()->GetRotation().Z);
		}

		node = node->GetNext();
	}

	m_World->Step(dt, VelocityIterations, PositionIterations);
	m_World->ClearForces();

	node = m_World->GetBodyList();
	Vector3 vec3D;
	while (node)
	{
		if (node->GetType() != b2_staticBody)
		{
			body = ((IBody*)node->GetUserData());

			if (body)
			{
				object = body->GetHolder();
				const b2Vec2 &pos = node->GetPosition();
				const Vector3 &parentPos = object->GetTransform()->GetParent()->GetPosition();

				vec3D.X = pos.x - parentPos.X;
				vec3D.Y = pos.y - parentPos.Y;
				vec3D.Z = object->GetTransform()->GetLocalPosition().Z;

				object->GetTransform()->SetRotation(node->GetAngle() * Math::RADIANS_TO_DEGREES);
				object->GetTransform()->SetPosition(vec3D);
			}
		}

		node = node->GetNext();
	}
}


IBody *PhysicsScene::CreateBody(IGameObject *GameObject)
{
	return new Body(GameObject, this);
}


void PhysicsScene::DestroyBody(IBody *Body)
{
	JointList::Iterator it = m_JointsList.GetFirst();

	// We cannot delete the joints by FOR_EACH
	// But we can do this in following way

	//IJoint *joint = NULL;
	//FOR_EACH(object, m_JointsList)
	//{
	//	joint = *object;

	//	if ((*it)->GetBodyA() == Body || (*it)->GetBodyB() == Body)
	//	{
	//		delete &it;

	//		m_JointsList.Remove(it);
	//	}

	//}

	while (it != m_JointsList.GetEnd())
	{
		if (it->GetBodyA() == Body || it->GetBodyB() == Body)
		{
			delete &it;

			//m_JointsList.Remove(it);
		}
		else
			it++;
	}

	delete Body;
	Body = 0;
}


IJoint *PhysicsScene::CreateRevoluteJoint(const String &Name,
										   IBody *BodyA,
										   IBody *BodyB,
										   bool CollideConnected,
										   const Vector2 &LocalAnchorA,
										   const Vector2 &LocalAnchorB,
										   float32 ReferenceAngle)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IRevoluteJoint *joint = new RevoluteJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAnchorA, LocalAnchorB, ReferenceAngle);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreatePrismaticJoint(const String &Name,
											IBody *BodyA,
											IBody *BodyB,
											bool CollideConnected,
											const Vector2 &LocalAxisA,
											const Vector2 &LocalAnchorA,
											const Vector2 &LocalAnchorB,
											float32 ReferenceAngle)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IPrismaticJoint *joint = new PrismaticJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAxisA, LocalAnchorA, LocalAnchorB, ReferenceAngle);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreateDistanceJoint(const String &Name,
										   IBody *BodyA,
										   IBody *BodyB,
										   bool CollideConnected,
										   const Vector2 &LocalAnchorA,
										   const Vector2 &LocalAnchorB)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IDistanceJoint *joint = new DistanceJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAnchorA, LocalAnchorB);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreateRopeJoint(const String &Name,
									   IBody *BodyA,
									   IBody *BodyB,
									   bool CollideConnected,
									   const Vector2 &LocalAnchorA,
									   const Vector2 &LocalAnchorB)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IRopeJoint *joint = new RopeJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAnchorA, LocalAnchorB);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreatePulleyJoint(const String &Name,
										 IBody *BodyA,
										 IBody *BodyB,
						  				 bool CollideConnected,
										 const Vector2 &GroundAnchorA,
										 const Vector2 &LocalAnchorA,
										 const Vector2 &GroundAnchorB,
										 const Vector2 &LocalAnchorB,
										 const float LengthA,
										 const float LengthB,
										 const float Ratio)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IPulleyJoint *joint = new PulleyJoint(this, Name, BodyA, BodyB, CollideConnected, GroundAnchorA, LocalAnchorA, GroundAnchorB,  LocalAnchorB, LengthA, LengthB, Ratio);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreateGearJoint(const String &Name,
									   IBody *BodyA,
									   IBody *BodyB,
						  			   bool CollideConnected,
									   IRevoluteJoint *RevoluteJoint,
									   IPrismaticJoint *PrismaticJoint)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IGearJoint *joint = new GearJoint(this, Name, BodyA, BodyB, CollideConnected, RevoluteJoint, PrismaticJoint);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreateWheelJoint(const String &Name,
										IBody *BodyA,
										IBody *BodyB,
										bool CollideConnected,
										const Vector2 &LocalAxisA,
										const Vector2 &LocalAnchorA,
										const Vector2 &LocalAnchorB)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IWheelJoint *joint = new WheelJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAxisA, LocalAnchorA, LocalAnchorB);
	m_JointsList.Add(joint);
	return joint;
}


IJoint *PhysicsScene::CreateWeldJoint(const String &Name,
									  IBody *BodyA,
									  IBody *BodyB,
									  bool CollideConnected,
									  const Vector2 &LocalAnchorA,
									  const Vector2 &LocalAnchorB,
									  float32 ReferenceAngle)
{
	if (GetJoint(Name))
	{
		LOG_ERROR("Joint with the name " + Name + " already exists")
		return NULL;
	}

	IWeldJoint *joint = new WeldJoint(this, Name, BodyA, BodyB, CollideConnected, LocalAnchorA, LocalAnchorB, ReferenceAngle);
	m_JointsList.Add(joint);
	return joint;
}


#ifndef LAUNCE_MODE
void PhysicsScene::AddJoint(IJoint *Joint)
{
	Joint->Prepare();
	//Joint->UndoChanges(Joint);
	m_JointsList.Add(Joint);
}


void PhysicsScene::RemoveJoint(IJoint *Joint)
{
	DestroyBox2DJoint((b2Joint*)Joint->GetData());

	m_JointsList.Remove(Joint);
}
#endif


void PhysicsScene::DestroyJoint(IJoint *Joint)
{
	m_JointsList.Remove(Joint);

	delete Joint;
}


 IJoint *PhysicsScene::GetJoint(const String &Name)
{
	FOR_EACH(it, m_JointsList)
		if (it->GetName() == Name)
			return &it;

	return NULL;
}


END_NAMESPACE
