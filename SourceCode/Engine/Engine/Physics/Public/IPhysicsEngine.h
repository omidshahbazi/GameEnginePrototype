// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPHYSICSENGINE_H
#define IPHYSICSENGINE_H

#include <Public\IPlugin.h>

BEGIN_NAMESPACE

class IPhysicsScene;

class IPhysicsEngine : public IPlugin
{
public:
	virtual ~IPhysicsEngine(void) {}

	virtual IPhysicsScene *CreatePhysicsScene(void) = 0;
	virtual void DestroyPhysicsScene(IPhysicsScene *Scene) = 0;
};

END_NAMESPACE
#endif // IPHYSICSENGINE_H
