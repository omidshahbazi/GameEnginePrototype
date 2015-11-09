// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\LauncherCommon.h>
#include <Public\Core.h>
#include <Public\Renderer\ICamera.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Renderer\MaterialResourcesManager.h>
#include <Public\Renderer\MeshResourcesManager.h>
#include <Public\Renderer\CompositeResourcesManager.h>
#include <Public\Renderer\IGPUProgramUsage.h>
#include <Public\NativeWindow.h>
#include <Public\IScene.h>
#include <Public\IGameObject.h>
#include <Public\ITransform.h>
#include <Public\Utility.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Renderer\IRenderer.h>
#include <Public\CTime.h>




#include <Windows.h>

USING_NAMESPACE

// Physics system as components
// sound and gui as components
// inputmanager per window
// material from fbx
// material format refine
// lighting

#ifdef FULL_DEBUG_MODE
int32 main(void)
#else
int32 WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInstance, LPSTR CMDLine, int32 ShowCMD)
#endif
{
	Core &core = Core::GetReference();
	core.Initialize();
	//core.SetTargetFPS(10);

	IRenderEngine *render = core.GetRenderer();
	IInputManager *input = core.GetInputManager();

	IScene *scene = core.CreateScene("");

	IGameObject *cameraObj0 = scene->CreateGameObject("Camera");
	cameraObj0->GetTransform()->SetPosition(0, 0, 10);
	ICamera *camera0 = cameraObj0->AddComponent<ICamera>("Camera");
	camera0->SetClearColour(Colour::RED);
	camera0->SetFarClipDistance(200);
	camera0->SetClearColour(Colour::WHITE);

	IRenderWindow *window0 = render->CreateRenderWindow("Test Window 0");
	window0->SetSize(Vector2(800, 600));
	window0->SetCamera(camera0);
	window0->Show();

	IMaterial *mat = MaterialResourcesManager::GetReference().GetMaterial("Test.material");
	IMesh *mesh = MeshResourcesManager::GetReference().GetMesh(BasicShapes::Cube);

	const String objName = "obj",
		rendererTypeName = "Renderer",
		testTypeName = "Test";

	IGameObject *obj = scene->CreateGameObject("obj");
	IRenderer *ren = obj->AddComponent<IRenderer>(rendererTypeName);
	ren->SetMaterial(mat);
	ren->SetMesh(mesh);

	IGameObject *obj0 = NULL;
	for (float32 i = 0; i < 1000; i++)
	{
		obj0 = scene->CreateGameObject(objName, obj0);

		IRenderer *ren = obj0->AddComponent<IRenderer>(rendererTypeName);
		ren->SetMaterial(mat);
		ren->SetMesh(mesh);

		//obj0->AddComponent(testTypeName);
		obj0->GetTransform()->SetPosition(0.05F * i, 0.05F * i, 0);
	}


	while (true)
	{
		core.UpdateOneFrame();
	}

	return core.Shutdown();
	
	////CompositeResourcesManager &comManager = CompositeResourcesManager::GetReference();
	////IComposite *blur = comManager.GetCompoiste("Blur.composite");
	////IComposite *gaussianBlur = comManager.GetCompoiste("GaussianBlur.composite");
	////IComposite *invert = comManager.GetCompoiste("Invert.composite");
	////IComposite *hdr = comManager.GetCompoiste("HDR.composite");
	////IComposite *simple = comManager.GetCompoiste("Simple.composite");
	////IComposite *mask = comManager.GetCompoiste("Mask.composite");


	//IScene *scene = core.CreateScene("");

	//IGameObject *cameraObj0 = scene->CreateGameObject("Camera");
	//cameraObj0->GetTransform()->SetPosition(0, 0, 100);
	////cameraObj0->AddComponent("Test");
	//ICamera *camera0 = cameraObj0->AddComponent<ICamera>("Camera");
	////camera0 = cameraObj->GetComponent<ICamera>("Camera");
	////camera0->SetProjectionType(ICamera::PT_ORTHOGRAPHIC);
	//camera0->SetClearColour(Colour::RED);
	//camera0->SetFarClipDistance(200);
	//camera0->SetClearColour(Colour::WHITE);
	////cameraObj0->AddComponent("CameraController");
	////camera0->AddComposite(gaussianBlur);

	//IRenderWindow *window0 = render->CreateRenderWindow("Test Window 0");
	//window0->SetSize(Vector2(800, 600));
	//window0->SetCamera(camera0);
	//window0->Show();


	//IGameObject *cameraObj1 = scene->CreateGameObject("Camera");
	//cameraObj1->GetTransform()->SetPosition(0, 0, 10);
	//ICamera *camera1 = cameraObj1->AddComponent<ICamera>("Camera");
	//camera1->SetFarClipDistance(1000.0F);
	//camera1->SetClearColour(Colour::WHITE);
	////camera0->AddComposite(hdr);

	////IRenderWindow *window1 = render->CreateRenderWindow("Test Window 1");
	////window1->SetSize(Vector2(500, 500));
	////window1->SetCamera(camera1);
	////window1->Show();


	////IGameObject *cameraObj2 = scene->CreateGameObject("Camera");
	////cameraObj2->GetTransform()->SetPosition(0, 0, 10);
	////ICamera *camera2 = cameraObj2->AddComponent<ICamera>("Camera");
	////camera2->SetFarClipDistance(1000.0F);
	////camera2->SetClearColour(Colour::WHITE);
	//////camera2->AddComposite(invert);

	////IRenderWindow *window2 = render->CreateRenderWindow("Test Window 2");
	////window2->SetSize(Vector2(500, 500));
	////window2->SetCamera(camera2);
	////window2->Show();


	////IGameObject *cameraObj3 = scene->CreateGameObject("Camera");
	////cameraObj3->GetTransform()->SetPosition(0, 0, 10);
	////ICamera *camera3 = cameraObj3->AddComponent<ICamera>("Camera");
	////camera3->SetFarClipDistance(1000.0F);
	////camera3->SetClearColour(Colour::WHITE);
	//////camera3->AddComposite(blur);

	////IRenderWindow *window3 = render->CreateRenderWindow("Test Window 3");
	////window3->SetSize(Vector2(500, 500));
	////window3->SetCamera(camera3);
	////window3->Show();


	////IGameObject *cameraObj4 = scene->CreateGameObject("Camera");
	////cameraObj4->GetTransform()->SetPosition(0, 0, 10);
	////ICamera *camera4 = cameraObj4->AddComponent<ICamera>("Camera");
	////camera4->SetFarClipDistance(1000.0F);
	//////camera4->AddComposite(gaussianBlur);

	////IRenderWindow *window4 = render->CreateRenderWindow("Test Window 4");
	////window4->SetSize(Vector2(500, 500));
	////window4->SetCamera(camera4);
	////window4->Show();

	//IMaterial *mat = MaterialResourcesManager::GetReference().GetMaterial("Test.material");
	////IMaterial *mat = MaterialResourcesManager::GetReference().GetMaterial("WithoutShader.material");
	////IMaterial *mat = MaterialResourcesManager::GetReference().GetMaterial("AlphaTest.material");

	////IMaterial *mat = MaterialResourcesManager::GetReference().CreateMaterial("Dummy");
	////mat->GetPass(0)->SetTexture(TextureResourcesManager::GetReference().GetTexture("Cube/Cube.png"));

	////IRenderTarget *rt1 = TextureResourcesManager::GetReference().CreateRenderTarget("rt1", Vector2(800, 600));
	////rt1->SetCamera(camera1);
	////mat->GetPass(0)->SetTextureStage(0, rt1);

	//IMesh *mesh = MeshResourcesManager::GetReference().GetMesh(BasicShapes::Cube);
	////IMesh *mesh = MeshResourcesManager::GetReference().GetMesh("SuperMan/SuperMan.FBX");

	//const String objName = "obj",
	//	rendererTypeName = "Renderer",
	//	testTypeName = "Test";

	//LARGE_INTEGER l1;
	//QueryPerformanceCounter(&l1);

	//IGameObject *obj = scene->CreateGameObject("obj");
	//IRenderer *ren = obj->AddComponent<IRenderer>(rendererTypeName);
	//ren->SetMaterial(mat);
	//ren->SetMesh(mesh);
	////obj->GetTransform()->SetLocalScale(Vector3(2, 2, 1));
	////obj->AddComponent(testTypeName);


	////IGameObject *obj0 = NULL;
	////for (float32 i = 0; i < 1000; i++)
	////{
	////	obj0 = scene->CreateGameObject(objName, obj0);

	////	IRenderer *ren = obj0->AddComponent<IRenderer>(rendererTypeName);
	////	//ren->SetMaterial(mat);
	////	ren->SetMesh(mesh);

	////	//obj0->AddComponent(testTypeName);
	////	obj0->GetTransform()->SetPosition(0.05F * i, 0.05F * i, 0);
	////}

	////int32 z = 0;
	////for (z = 0; z < 2; z++)
	////{
	////	for (int32 y = 0; y < 20; y++)
	////	{
	////		for (int32 x = 0; x < 20; x++)
	////		{
	////			IGameObject *obj = scene->CreateGameObject(objName, obj0);

	////			IRenderer *ren = obj->AddComponent<IRenderer>(rendererTypeName);
	////			ren->SetMaterial(mat);
	////			ren->SetMesh(mesh);

	////			obj->AddComponent(testTypeName);
	////			obj->GetTransform()->SetPosition(x, y, 0);
	////		}
	////	}
	////}

	//LARGE_INTEGER l2;
	//QueryPerformanceCounter(&l2);

	//LARGE_INTEGER freq;
	//QueryPerformanceFrequency(&freq);

	//double time = ((double)(l2.QuadPart - l1.QuadPart) / (double)freq.QuadPart);

	////mat->GetPass(0)->SetFillMode(FillModes::WIREFRAME);

	////Time::GetReference().SetTimeScale(0.1F);


	//while (true)
	//{
	//	core.UpdateOneFrame();
	//	//if (input->IsKeyPressed(K_1))
	//	//	mat->GetPass(0)->SetFillMode(FillModes::SOLID);
	//	//else if (input->IsKeyPressed(K_2))
	//	//	mat->GetPass(0)->SetFillMode(FillModes::WIREFRAME);
	//	//else if (input->IsKeyPressed(K_3))
	//	//	mat->GetPass(0)->SetFillMode(FillModes::POINT);
	//}

	//return core.Shutdown();
}
