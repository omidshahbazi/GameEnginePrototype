// Copyright 2012-2015 ?????????????. All Rights Reserved.

#include <Public\Component.h>
#include <Private\ComponentManager.h>
#include <Private\Scene.h>
#include <Private\GameObject.h>

BEGIN_NAMESPACE


void Component::SetEnabled(bool Value)
{
	if (m_Enabled == Value)
		return;

	m_Enabled = Value;

	ComponentManager *comMan = ((Scene*)m_Holder->GetHolder())->GetComponentManager();
	comMan->SetEnabled(this, Value);
}


END_NAMESPACE
