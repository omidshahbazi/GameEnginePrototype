// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CORE_H
#define CORE_H

#include <Public\Common.h>
#include <Public\Singleton.h>
#include <Public\ListenerHolder.h>
#include <Public\ActiveVector.h>
#include <Public\FrameStats.h>

BEGIN_NAMESPACE

class IScene;
class IInputManager;
class IRenderEngine;
class IPhysicsEngine;
class ISoundSystem;
class IGUISystem;


class CORE_API Core
{
	DECLARE_SINGLETON(Core)

	BEGIN_DECLARE_LISTENER_HOLDER
		virtual void OnBeforeSceneRemoved(IScene *Scene) = 0;
	virtual void OnSceneAdded(IScene *Scene) = 0;

	virtual void OnSetCurrentScene(IScene *Scene) = 0;

	virtual void OnBeforeUpdate(void) = 0;
	virtual void OnAfterUpdate(void) = 0;

	virtual void OnBeforeRender(void) = 0;
	virtual void OnAfterRender(void) = 0;
	END_DECLARE_LISTENER_HOLDER

private:
	Core(void);
	~Core(void);

public:
	int32 Shutdown(void);

	void Initialize(void);

public:
	void UpdateOneFrame(void);

	IScene *CreateScene(const String &Name);
	void DestroyScene(IScene *Scene);
	IScene *GetScene(const String &Name);

	void InitializeDataPath(const String &Path = "");

public:
	const String &GetEngineName(void) const
	{
		return m_EngineName;
	}

	const String &GetInitializePath(void) const
	{
		return m_InitializePath;
	}

	const String &GetDataPath(void) const
	{
		return m_DataPath;
	}

	void SetInputManager(IInputManager *InputManager)
	{
		m_InputManager = InputManager;
	}

	IInputManager *GetInputManager(void) const
	{
		return m_InputManager;
	}

	void SetRenderer(IRenderEngine *Renderer)
	{
		m_Renderer = Renderer;
	}

	IRenderEngine *GetRenderer(void) const
	{
		return m_Renderer;
	}

	void SetPhysics(IPhysicsEngine *Physics)
	{
		m_Physics = Physics;
	}

	IPhysicsEngine *GetPhysics(void) const
	{
		return m_Physics;
	}

	void SetSoundSystem(ISoundSystem *SoundSystem)
	{
		m_SoundSystem = SoundSystem;
	}

	ISoundSystem* GetSoundSystem(void)
	{
		return m_SoundSystem;
	}

	void SetGUISystem(IGUISystem *GUISystem)
	{
		m_GUISystem = GUISystem;
	}

	IGUISystem* GetGUISystem(void)
	{
		return m_GUISystem;
	}

	bool GetIsInitialized(void) const
	{
		return m_IsInitialized;
	}

	const FrameStats &GetFrameStats(void) const
	{
		return m_FrameStats;
	}

private:
	typedef ActiveVector<IScene*> ScenesList;

	String m_EngineName;
	String m_InitializePath;
	String m_DataPath;

	FrameStats m_FrameStats;

	IInputManager *m_InputManager;
	IRenderEngine *m_Renderer;
	IPhysicsEngine *m_Physics;
	ISoundSystem *m_SoundSystem;
	IGUISystem *m_GUISystem;

	bool m_IsInitialized;

	ScenesList m_Scenes;
};

END_NAMESPACE
#endif // CORE_H
