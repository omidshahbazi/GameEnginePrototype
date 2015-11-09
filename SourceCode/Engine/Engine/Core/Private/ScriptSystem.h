// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H
#include <Public\Common.h>
#include <Public\Component.h>
#include <Windows.h>

BEGIN_NAMESPACE

class IGameObject;

class ScriptSystem
{
	DECLARE_SINGLETON(ScriptSystem)

private:
	ScriptSystem(void);

public:
	void Recompile(void);

	Component *Instantiate(const String &ComponentType);

private:
	void Load(void);
	void Unload(void);

private:
	int32 m_Handle;
};

END_NAMESPACE
#endif // SCRIPTSYSTEM_H
