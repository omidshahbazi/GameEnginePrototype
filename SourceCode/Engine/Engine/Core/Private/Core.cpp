// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Core.h>
#include <Private\Scene.h>
#include <Public\PluginManager.h>
#include <Public\CTime.h>
#include <Private\ScriptSystem.h>
#include <Public\Renderer\IRenderEngine.h>
//#include "Public/Input/IInputManager.h"
//#include "Public/Renderer/ICamera.h"
//#include "Public/Physics/IPhysicsEngine.h"
//#include "Public/SoundSystem/ISoundSystem.h"
//#include "Public/GUISystem/IGUISystem.h"
#include <Public\WindowUtility.h>
#include <Public\StringUtility.h>
#include <Public\Utility.h>
#include <Private\GameObject.h>


#ifdef _DEBUG
#include <Private\Statistics.h>
#endif

//#include <Public\StringConverter.h>
//#include <Public\Enum.h>
//#include <Public\Transform.h>


BEGIN_NAMESPACE

DEFINE_SINGLETON(Core)

Core::Core(void) :
m_InputManager(NULL),
m_Renderer(NULL),
m_Physics(NULL),
m_SoundSystem(NULL),
m_GUISystem(NULL),
m_IsInitialized(false)
{
}


Core::~Core(void)
{
	Shutdown();
}


int32 Core::Shutdown(void)
{
	for (uint32 i = 0; i < m_Scenes.GetSize(); i++)
		delete &m_Scenes[i];

	delete m_Physics;
	delete m_GUISystem;
	delete m_Renderer;
	delete m_SoundSystem;
	delete m_InputManager;

	return 0;
}


void Core::Initialize(void)
{
	//String str = Enum::ToString("TransformationSpace", (int32)TransformationSpaces::World);

	//GameObject g(NULL, "Fucking GO", NULL);

	///*FunctionType *const setNameFunc = typeof(IE::GameObject).GetFunction("SetName");
	//setNameFunc->Invoke(&g, String("Omid"));*/

	//const FunctionType *const getNameFunc = typeof(IE::GameObject).GetFunction("GetTransform");
	//Transform *tr = (Transform *)getNameFunc->Invoke(&g).GetAsVoid();

	m_EngineName = "??????????????????????";

	char path[1024];
	DWORD length = GetModuleFileName(GetModuleHandle(NULL), path, 1024);
	path[length] = '\0';

	StringUtility::SplitFilename(path, NULL, &m_InitializePath);

	InitializeDataPath();

	ScriptSystem::GetReference().Recompile();

	PluginManager &plugins = PluginManager::GetReference();
	//plugins.LoadPlugin("Input.dll");
	//plugins.LoadPlugin("Physics.dll");
	plugins.LoadPlugin("D3DRenderer.dll");
	//plugins.LoadPlugin("SoundSystem.dll");
	//plugins.LoadPlugin("GUISystem.dll");

	if (m_Renderer)
		m_Renderer->Initialize();

	////if (m_InputManager)
	////	m_InputManager->Initialize(WindowHandle);

	//if (m_SoundSystem)
	//	m_SoundSystem->Initialize();

	//if (m_GUISystem)
	//	m_GUISystem->Initialize();

	m_IsInitialized = true;
}


void Core::UpdateOneFrame(void)
{
	if (!m_IsInitialized)
		return;

	static Time &time = Time::GetReference();
	static float32 realTime = 0.0F;
	static float32 sumFramesTime = 0.0F;
	static uint16 framesCount = 0;
	static float32 lastFPSChangeTime = 0.0F;

	time.Tick();

	WindowUtility::PumpMessages();

	if (time.GetRealTime() - realTime < m_FrameStats.TargetFrameTime)
		return;
	//
	// Update everything here
	//
	//	FOR_EACH(listener, m_Listeners)
	//		listener->OnBeforeUpdate();
	//
	//	if (m_InputManager)
	//		m_InputManager->Update();
	//
	//	//if (m_Physics)
	//	//	m_Physics->Update();
	//
	if (m_Renderer)
		m_Renderer->Update();
	//
	//	if (m_SoundSystem)
	//		m_SoundSystem->Update();
	//
	for (uint32 i = 0; i < m_Scenes.GetActiveCount(); i++)
	{
		IScene *scene = m_Scenes[i];
		scene->PreUpdate();
		scene->Update();
	}

	//if (m_InputManager)
	//	m_InputManager->PostUpdate();

	FOR_EACH(listener, m_Listeners)
		listener->OnAfterUpdate();
	//
	//#ifdef _DEBUG
	//	static Statistics &stats = Statistics::GetReference();
	//	stats.Update();
	//#endif
	//
	//
	// Render Everything here
	//
	if (m_Renderer)
	{
		FOR_EACH(listener, m_Listeners)
			listener->OnBeforeRender();

		for (uint32 i = 0; i < m_Scenes.GetActiveCount(); i++)
			m_Scenes[i]->PreRender();

		m_Renderer->Render();

		FOR_EACH(listener, m_Listeners)
			listener->OnAfterRender();
	}

	sumFramesTime += (time.GetRealTime() - realTime);
	realTime = time.GetRealTime();

	if (realTime - lastFPSChangeTime > 1.0F)
	{
		lastFPSChangeTime = realTime;

		m_FrameStats.FPS = framesCount;
		framesCount = 0;

		m_FrameStats.AverageFrameTime = (sumFramesTime / m_FrameStats.FPS) * 1000.0F;
		sumFramesTime = 0.0F;

		std::cout << m_FrameStats.FPS << " - " << m_FrameStats.AverageFrameTime << "\n";
	}
	else
		framesCount++;
}


IScene *Core::CreateScene(const String &Name)
{
	Scene *scene = new Scene(Name);

	m_Scenes.Add(scene);

	return scene;
}


void Core::DestroyScene(IScene *Scene)
{
	if (!Scene)
	{
		LOG_ERROR("Scene to destroy cannot be NULL")
			return;
	}

	//if (m_CurrentScene == Scene)
	//	SetCurrentScene(NULL);

	//FOR_EACH(listener, m_Listeners)
	//	listener->OnBeforeSceneRemoved(Scene);

	//m_Scenes.Remove(FIND_ITERATOR(Scene, m_Scenes));

	delete Scene;
}


IScene *Core::GetScene(const String &Name)
{
	//FOR_EACH(scene, m_Scenes)
	//if (scene->GetName() == Name)
	//	return &scene;

	return NULL;
}


void Core::InitializeDataPath(const String &Path)
{
	m_DataPath = Path;

	if (m_DataPath.GetLength())
	{
		m_DataPath.Replace("\\", "/");

		if (!m_DataPath.EndsWith("/"))
			m_DataPath += "/";
	}
	else
		m_DataPath = m_InitializePath + "Data/";
}

END_NAMESPACE
