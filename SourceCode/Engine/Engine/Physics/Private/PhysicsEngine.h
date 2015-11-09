// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Public\IPlugin.h>
#include <Public\Physics\IPhysicsEngine.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class ContactListener;

class PhysicsEngine : public IPhysicsEngine
{
public:
	virtual ~PhysicsEngine(void);

	void Install(void);
	const String &GetName(void) const
	{
		static String name = "Box2D Physics Engine";
		return name;
	}
	const String &GetVersion(void) const
	{
		static String version = "1.0.0.0";
		return version;
	}

	IPhysicsScene *CreatePhysicsScene(void);
	void DestroyPhysicsScene(IPhysicsScene *Scene);


private:
	typedef Vector<IPhysicsScene*> PhysicsScenesList;

	PhysicsScenesList m_ScenesList;
};

END_NAMESPACE
#endif // PHYSICSENGINE_H
