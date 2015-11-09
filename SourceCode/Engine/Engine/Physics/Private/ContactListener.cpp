// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ContactListener.h>
#include <Public\Physics\IBody.h>
#include <Private\Contact.h>
//#include "IScene.h"
#include <Public\IGameObject.h>


BEGIN_NAMESPACE


void CallContactFunction(b2Contact* contact, Vector2 *Points, uint32 PointCount, const String &Function, const bool ForFixtueB)
{
	void* bodyUserData = NULL;
	Contact *contactData = NULL;

	if (!ForFixtueB)
	{
		bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		contactData = new Contact(static_cast<IFixture*>(contact->GetFixtureB()->GetUserData()), Points, PointCount);
	}
	else
	{
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		contactData = new Contact(static_cast<IFixture*>(contact->GetFixtureA()->GetUserData()), Points, PointCount);
	}

	IBody *body = static_cast<IBody*>(bodyUserData);
	if (body)
	{
		body->SetContact(contactData);

		body->SetContact(NULL);
	}

	delete contactData;
}


ContactListener::ContactListener(void)
{
	m_Manifold = new b2WorldManifold;
}


ContactListener::~ContactListener(void)
{
	delete m_Manifold;
}


void ContactListener::BeginContact(b2Contact* contact)
{
	NotifyContact(contact, "BeginContact");
}


void ContactListener::EndContact(b2Contact* contact)
{
	NotifyContact(contact, "EndContact");
}


void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	NotifyContact(contact, "PreSolve");
}


void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	NotifyContact(contact, "PostSolve");
}


void ContactListener::NotifyContact(b2Contact* contact, const String &Function)
{
	unsigned int pointCount = 0;
	Vector2 *points = GetContactPoints(contact, pointCount, true);

	CallContactFunction(contact, points, pointCount, Function, false);

	CallContactFunction(contact, points, pointCount, Function, true);

	delete []points;
}


Vector2 *ContactListener::GetContactPoints(b2Contact* contact, uint32 PointCount, bool UseOldManifold)
{
	contact->GetWorldManifold(m_Manifold);

	PointCount = contact->GetManifold()->pointCount;

	Vector2 *points = new Vector2[PointCount];

	for (unsigned int i = 0; i < PointCount; i++)
		points[i] = Vector2(m_Manifold->points[i].x, m_Manifold->points[i].y);

	return points;
}


END_NAMESPACE
