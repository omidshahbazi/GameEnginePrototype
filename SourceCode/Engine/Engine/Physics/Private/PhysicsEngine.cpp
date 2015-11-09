// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\PhysicsEngine.h>
#include <Private\PhysicsScene.h>
#include <Public\Core.h>


BEGIN_NAMESPACE


PhysicsEngine::~PhysicsEngine(void)
{
	if (m_ScenesList.GetSize())
		THROW_EXCEPTION_AND_RESUME(Exception::ER_PERFORMANCE_HIT, "There's some IPhysicsScene that didn't destroyed through their holder IScene(s)", "PhysicsEngine::~PhysicsEngine")
	
	LOG_INFO_DEBUG("IPhysicsEngine destoryed successfully")
}


void PhysicsEngine::Install(void)
{
	Core::GetReference().SetPhysics(this);
}


IPhysicsScene *PhysicsEngine::CreatePhysicsScene(void)
{
	IPhysicsScene *Scene = new PhysicsScene();
	m_ScenesList.Add(Scene);
	return Scene;
}


void PhysicsEngine::DestroyPhysicsScene(IPhysicsScene *Scene)
{
	m_ScenesList.Remove(Scene);

	delete Scene;
}


END_NAMESPACE
