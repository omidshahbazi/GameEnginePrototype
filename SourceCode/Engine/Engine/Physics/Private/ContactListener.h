// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Public\Vector2.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class IContact;

class ContactListener : public b2ContactListener
{
public:
	ContactListener(void);
	~ContactListener(void);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

private:
	void NotifyContact(b2Contact* contact, const String &Function);
	Vector2 *GetContactPoints(b2Contact* contact, uint32 PointCount, bool UseOldManifold = false);

private:
	b2WorldManifold *m_Manifold;
};

END_NAMESPACE
#endif // CONTACTLISTENER_H
