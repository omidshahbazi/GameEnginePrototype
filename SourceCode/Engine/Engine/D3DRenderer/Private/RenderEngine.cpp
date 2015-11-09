// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\RenderEngine.h>
#include <Public\Core.h>
#include <Public\StringConverter.h>
#include <Public\Renderer\IMesh.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Renderer\MaterialResourcesManager.h>
#include <Public\Renderer\MeshResourcesManager.h>
#include <Public\Renderer\CompositeResourcesManager.h>
#include <Public\FileIO.h>
#include <Public\CTime.h>
#include <Private\TextureResourcesFactory.h>
#include <Private\GPUProgramResourcesFactory.h>
#include <Private\MaterialResourcesFactory.h>
#include <Private\MeshResourcesFactory.h>
#include <Private\CompositeResourcesFactory.h>
#include <Private\RenderWindow.h>
#include <Private\Camera.h>
#include <Private\Renderer.h>
#include <Private\Texture.h>
#include <Private\GPUProgramUsage.h>
#include <Private\MovieManager.h>
#include <Public\ThreadManager.h>
#include <Private\RendererCommon.h>

BEGIN_NAMESPACE


const String BASIC_VERTEX_PROGRAM("uniform float4x4 WVP; struct VS_Output { float4 Position : POSITION;	float4 Color : COLOR0; float2 TexCoord : TEXCOORD0; }; VS_Output vMain(float4 Position : POSITION, float4 Color : COLOR0, float2 TexCoord : TEXCOORD0) { VS_Output output; output.Position = mul(Position, WVP); output.Color = Color; output.TexCoord = TexCoord; return output; }");

uint64 primitivesCount;

RenderEngine::RenderEngine(void) :
m_Direct3D(NULL),
m_Device(NULL)
{
	m_GPUParams[GPUParamDefinition::WORLD_MATRIX] = Matrix4::IDENTITY;
	m_GPUParams[GPUParamDefinition::VIEW_MATRIX] = Matrix4::IDENTITY;
	m_GPUParams[GPUParamDefinition::PROJECTION_MATRIX] = Matrix4::IDENTITY;
	m_GPUParams[GPUParamDefinition::WORLDVIEWPROJECTION_MATRIX] = Matrix4::IDENTITY;

	m_GPUParams[GPUParamDefinition::TIME] = 0.0F;
	m_GPUParams[GPUParamDefinition::REAL_TIME] = 0.0F;

	m_GPUParams[GPUParamDefinition::NEAR_CLIP_DISTANCE] = 0.0F;
	m_GPUParams[GPUParamDefinition::FAR_CLIP_DISTANCE] = 0.0F;

	m_GPUParams[GPUParamDefinition::TARGET_SIZE] = Vector2::ZERO;
	m_GPUParams[GPUParamDefinition::ASPECT_RATIO] = 0.0F;
}


RenderEngine::~RenderEngine(void)
{
}


void RenderEngine::Install(void)
{
	Core::GetReference().SetRenderer(this);
}


void RenderEngine::Update(void)
{
	static Time &time = Time::GetReference();
	m_GPUParams[GPUParamDefinition::TIME] = time.GetTime();
	m_GPUParams[GPUParamDefinition::REAL_TIME] = time.GetRealTime();
}


void RenderEngine::Render(void)
{
	primitivesCount = 0;

	m_Device->BeginScene();

	FOR_EACH(rt, m_RenderTargets)
	{
		IRenderTarget *target = &rt;
		m_CurrentCamera = (Camera*)target->GetCamera();

		//m_CurrentCamera->GetProperty("")

		if (!m_CurrentCamera || !m_CurrentCamera->GetEnabled())
			continue;

		m_CurrentScene = m_CurrentCamera->GetHolder()->GetHolder();

		if (!m_CurrentScene->GetActive())
			continue;

		const Vector2 &targetSize = target->GetSize();

		m_CurrentCamera->SetTargetSize(targetSize);

		m_GPUParams[GPUParamDefinition::NEAR_CLIP_DISTANCE] = m_CurrentCamera->GetNearClipDistance();
		m_GPUParams[GPUParamDefinition::FAR_CLIP_DISTANCE] = m_CurrentCamera->GetFarClipDistance();

		m_GPUParams[GPUParamDefinition::TARGET_SIZE] = targetSize;
		m_GPUParams[GPUParamDefinition::ASPECT_RATIO] = m_CurrentCamera->GetAspectRatio();

		const ICamera::CompositesList &composites = m_CurrentCamera->GetComposites();
		const uint32 compositesCount = composites.GetSize();

		if (compositesCount)
		{
			static IMesh *quad = NULL;
			static Pass quadPass;
			static Matrix4 quadMat(true);
			static RenderTargetTexture sceneRTT(Vector2::ZERO, ColourFormats::A1R5G5B5);
			static RenderTargetTexture chainRTT0(Vector2::ZERO, ColourFormats::A1R5G5B5);
			static RenderTargetTexture chainRTT1(Vector2::ZERO, ColourFormats::A1R5G5B5);
			static RenderTargetTexture *pChainRTT0 = &chainRTT0;
			static RenderTargetTexture *pChainRTT1 = &chainRTT1;
			static const DWORD flags = D3DCLEAR_TARGET;

			if (!quad)
			{
				quad = MeshResourcesManager::GetReference().GetMesh(BasicShapes::Quad);

				quadMat.SetScale(2, 2, 1);

				quadPass.SetCullType(CullTypes::None);
			}

			sceneRTT.SetSize(targetSize);
			chainRTT0.SetSize(targetSize);
			chainRTT1.SetSize(targetSize);

			SetRenderTargetStage(0, &sceneRTT);
			SetRenderTargetStage(1, pChainRTT0);
			SetRenderTargetStage(2, pChainRTT1);
			RenderCurrentScene();

			SetViewMatrix(Matrix4::IDENTITY);
			SetProjectionMatrix(Matrix4::IDENTITY);
			SetWorldMatrix(quadMat);

			SetPass(&quadPass);

			const uint8 compositesCount = (uint8)composites.GetSize();

			IComposite *com = NULL;
			ICompositePass *pass = NULL;
			for (uint8 c = 0; c < compositesCount; c++)
			{
				com = composites[c];

				const IComposite::PassesList &passes = com->GetPasses();
				const uint8 passesCount = (uint8)passes.GetSize();

				for (uint8 p = 0; p < passesCount; p++)
				{
					pass = passes[p];

					for (uint8 t = 0; t < m_MaxSupportedTexturesCount; t++)
					{
						ICompositePass::InputStage &stage = pass->GetInputStage(t);

						if (stage.InputType == CompositeInputTypes::Scene)
							SetTextureStage(t, (RenderTarget*)&sceneRTT);
						else if (stage.InputType == CompositeInputTypes::Previous)
							SetTextureStage(t, (RenderTarget*)pChainRTT0);
						else if (stage.InputType == CompositeInputTypes::RenderTarget)
							SetTextureStage(t, stage.Texture);
						else
							SetTextureStage(t, NULL);
					}

					if (c + 1 == compositesCount && p + 1 == passesCount)
						SetRenderTargetStage(0, target);
					else
					{
						if (pass->GetTarget())
							SetRenderTargetStage(0, pass->GetTarget());
						else
							SetRenderTargetStage(0, (RenderTarget*)pChainRTT1);

						RenderTargetTexture *temp = pChainRTT1;
						pChainRTT1 = pChainRTT0;
						pChainRTT0 = temp;
						temp = NULL;
					}

					m_Device->Clear(0, NULL, flags, pass->GetClearColour().Value, 1.0F, 0);

					if (m_CurrentVertexProgram)
						m_Device->SetVertexShader(NULL);

					IGPUProgramUsage *usage = pass->GetProgram();
					if (m_CurrentFragmentProgram != usage->GetProgram())
					{
						m_CurrentFragmentProgram = (FragmentGPUProgram*)usage->GetProgram();

						m_Device->SetPixelShader(m_CurrentFragmentProgram ? m_CurrentFragmentProgram->GetShader() : NULL);
					}

					if (m_CurrentFragmentProgram)
						SetGPUProgramParams((GPUProgramUsage*)usage);

					DrawMesh(quad);
				}
			}
		}
		else
		{
			SetRenderTargetStage(0, target);

			RenderCurrentScene();
		}
	}

	m_Device->EndScene();

	FOR_EACH(window, m_RenderWindows)
		window->Present();
}


void RenderEngine::Initialize(void)
{
	const uint32 displayAdapter = 0;
	const bool verticalSync = false;
	const bool fullScreen = false;
	D3DDEVTYPE devtype = D3DDEVTYPE_HAL;
	int32 antiAlias = 0;
	DWORD multiSampleQualityLevels = 0;
	const bool stencilbuffer = true;
	const bool highPrecisionFPU = true;
	const bool multiThreaded = false;

	m_SupportsMRT = false;

	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);

#ifdef _DEBUG
	GetAdapterInfo(displayAdapter);
#endif

	D3DDISPLAYMODE d3ddm;
	m_Direct3D->GetAdapterDisplayMode(displayAdapter, &d3ddm);

	memset(&m_PresentParameters, NULL, sizeof(D3DPRESENT_PARAMETERS));

	m_PresentParameters.BackBufferCount = 1;
	m_PresentParameters.EnableAutoDepthStencil = TRUE;

	m_PresentParameters.PresentationInterval = verticalSync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	m_PresentParameters.BackBufferWidth = m_PresentParameters.BackBufferHeight = 1024;

	if (fullScreen)
	{
		m_PresentParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
		m_PresentParameters.SwapEffect = D3DSWAPEFFECT_FLIP;
		m_PresentParameters.Windowed = FALSE;
		m_PresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}
	else
	{
		m_PresentParameters.BackBufferFormat = d3ddm.Format;
		m_PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_PresentParameters.Windowed = TRUE;
	}

	while (antiAlias > 0)
	{
		if (SUCCEEDED(m_Direct3D->CheckDeviceMultiSampleType(displayAdapter, devtype, m_PresentParameters.BackBufferFormat, !fullScreen, (D3DMULTISAMPLE_TYPE)antiAlias, &multiSampleQualityLevels)))
		{
			m_PresentParameters.MultiSampleType = (D3DMULTISAMPLE_TYPE)antiAlias;
			m_PresentParameters.MultiSampleQuality = multiSampleQualityLevels - 1;
			m_PresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
			break;
		}
		antiAlias--;
	}

	if (stencilbuffer)
	{
		m_PresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
		if (FAILED(m_Direct3D->CheckDeviceFormat(displayAdapter, devtype, m_PresentParameters.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, m_PresentParameters.AutoDepthStencilFormat)))
		{
			m_PresentParameters.AutoDepthStencilFormat = D3DFMT_D24X4S4;
			if (FAILED(m_Direct3D->CheckDeviceFormat(displayAdapter, devtype, m_PresentParameters.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, m_PresentParameters.AutoDepthStencilFormat)))
			{
				m_PresentParameters.AutoDepthStencilFormat = D3DFMT_D15S1;
				if (FAILED(m_Direct3D->CheckDeviceFormat(displayAdapter, devtype, m_PresentParameters.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, m_PresentParameters.AutoDepthStencilFormat)))
					LOG_WARNING("Device does not support stencilbuffer, disabling stencil buffer")
			}
		}

		if (FAILED(m_Direct3D->CheckDepthStencilMatch(displayAdapter, devtype, m_PresentParameters.BackBufferFormat, m_PresentParameters.BackBufferFormat, m_PresentParameters.AutoDepthStencilFormat)))
			LOG_WARNING("Depth-stencil format is not compatible with display format, disabling stencil buffer")
	}

	//// do not use else here to cope with flag change in previous block
	//if (!Params.Stencilbuffer)
	//{
	//	present.AutoDepthStencilFormat = D3DFMT_D32;
	//	if (FAILED(pID3D->CheckDeviceFormat(adapter, devtype,
	//		present.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
	//		D3DRTYPE_SURFACE, present.AutoDepthStencilFormat)))
	//	{
	//		present.AutoDepthStencilFormat = D3DFMT_D24X8;
	//		if (FAILED(pID3D->CheckDeviceFormat(adapter, devtype,
	//			present.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
	//			D3DRTYPE_SURFACE, present.AutoDepthStencilFormat)))
	//		{
	//			present.AutoDepthStencilFormat = D3DFMT_D16;
	//			if (FAILED(pID3D->CheckDeviceFormat(adapter, devtype,
	//				present.BackBufferFormat, D3DUSAGE_DEPTHSTENCIL,
	//				D3DRTYPE_SURFACE, present.AutoDepthStencilFormat)))
	//			{
	//				os::Printer::log("Device does not support required depth buffer.", ELL_WARNING);
	//				return false;
	//			}
	//		}
	//	}
	//}

	DWORD fpuPrecision = highPrecisionFPU ? D3DCREATE_FPU_PRESERVE : 0;
	DWORD multithreaded = multiThreaded ? D3DCREATE_MULTITHREADED : 0;

	NativeWindow *dummyWindow = new NativeWindow("IE");

	if (FAILED(m_Direct3D->CreateDevice(displayAdapter, devtype, dummyWindow->GetHandle(), fpuPrecision | multithreaded | D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_PresentParameters, &m_Device)))
		LOG_ERROR("Was not able to create Direct3D9 device");

	LOG_INFO("Currently available Video-Memory " + StringConverter::ToString(m_Device->GetAvailableTextureMem() / 1073741824) + "GB")

		D3DCAPS9 caps;
	m_Device->GetDeviceCaps(&caps);

	//if (!(caps.DestBlendCaps & D3DRS_DESTBLENDALPHA))

	m_MaxSupportedRenderTargetsCount = (uint8)caps.NumSimultaneousRTs;
	m_MaxSupportedPrimitivesCount = (uint32)caps.MaxPrimitiveCount;
	m_MaxSupportedTexturesCount = (uint8)caps.MaxSimultaneousTextures;

	m_CurrentRenderTargets = new RenderTargetPointer[m_MaxSupportedRenderTargetsCount];
	memset(m_CurrentRenderTargets, NULL, m_MaxSupportedRenderTargetsCount * sizeof(RenderTargetPointer));

	m_CurrentTexutres = new Pass::TexturePointer[m_MaxSupportedTexturesCount];
	memset(m_CurrentTexutres, NULL, m_MaxSupportedTexturesCount * sizeof(Pass::TexturePointer));

	if (stencilbuffer &&
		(!(stencilbuffer & D3DSTENCILCAPS_DECRSAT) ||
		!(stencilbuffer & D3DSTENCILCAPS_INCRSAT) ||
		!(stencilbuffer & D3DSTENCILCAPS_KEEP)))
		LOG_WARNING("Device not able to use stencil buffer, disabling stencil buffer");

	SetVertexDeclaration(VertexDeclarations::Standard);

	//int32 ver = (((0x00ff00 & caps.VertexShaderVersion) >> 8) * 100 + (caps.VertexShaderVersion & 0xff));
	//int32 aver = (((0x00ff00 & caps.PixelShaderVersion) >> 8) * 100 + (caps.PixelShaderVersion & 0xff));

	m_Device->SetRenderState(D3DRS_FOGENABLE, FALSE);
	m_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_Device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	m_Device->SetRenderState(D3DRS_CLIPPING, TRUE);
	//m_Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	m_Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);

	SetRenderState(RenderStates::ThreeDimensional);

	//D3DFORMAT D3DColorFormat = D3DFMT_A8R8G8B8;
	//IDirect3DSurface9* bb = NULL;
	//if (SUCCEEDED(m_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bb)))
	//{
	//	D3DSURFACE_DESC desc;
	//	bb->GetDesc(&desc);
	//	D3DColorFormat = desc.Format;
	//	bb->Release();
	//}
	//ITexture::ColourFormat ColorFormat = TO_ColorFormat(D3DColorFormat);

	TextureResourcesManager::GetReference().Initialize(new TextureResourcesFactory);
	GPUProgramResourcesFactory *factory = new GPUProgramResourcesFactory;
	VertexGPUProgramResourcesManager::GetReference().Initialize(factory);
	FragmentGPUProgramResourcesManager::GetReference().Initialize(factory);
	MaterialResourcesManager::GetReference().Initialize(new MaterialResourcesFactory);
	MeshResourcesManager::GetReference().Initialize(new MeshResourcesFactory);
	CompositeResourcesManager::GetReference().Initialize(new CompositeResourcesFactory);

	IPass *pass = m_BaseMaterial.CreatePass();
	pass->SetVertexProgram(VertexGPUProgramResourcesManager::GetReference().CreateProgram("BasicVertexProgram", BASIC_VERTEX_PROGRAM, "vMain", VertexShaderTypes::v2));
	pass->GetVertexProgram()->SetAutoParam("WVP", GPUParamDefinition::WORLDVIEWPROJECTION_MATRIX);

	String fragmentProgram = "sampler2D tex;struct FS_Output{";

	//for (uint8 i = 0; i < m_MaxSupportedRenderTargetsCount; i++)
	for (uint8 i = 0; i < 1; i++)
	{
		const String num = StringConverter::ToString(i);
		fragmentProgram += "float4 Color" + num + ":COLOR" + num + ";";
	}

	//fragmentProgram += "};FS_Output fMain(float4 Color:COLOR,float2 TexCoord:TEXCOORD){float4 final=Color*tex2D(tex,TexCoord);FS_Output op;";
	fragmentProgram += "};FS_Output fMain(float4 Color:COLOR,float2 TexCoord:TEXCOORD){float4 final=Color*tex2D(tex,TexCoord);FS_Output op;";

	//for (uint8 i = 0; i < m_MaxSupportedRenderTargetsCount; i++)
	for (uint8 i = 0; i < 1; i++)
	{
		const String num = StringConverter::ToString(i);
		fragmentProgram += "op.Color" + num + "=final;";
	}

	fragmentProgram += "return op;}";

	pass->SetFragmentProgram(FragmentGPUProgramResourcesManager::GetReference().CreateProgram("BasicFragmentProgram", fragmentProgram, "fMain", FragmentShaderTypes::v2));
}


IRenderWindow *RenderEngine::CreateRenderWindow(const String &Text)
{
	RenderWindow *rw = new RenderWindow(Text);

	m_RenderWindows.Add(rw);

	rw->Show();

	return rw;
}


IRenderWindow *RenderEngine::CreateRenderWindow(WindowUtility::WindowHandle WindowHandle)
{
	RenderWindow *rw = new RenderWindow(WindowHandle);

	m_RenderWindows.Add(rw);

	return rw;
}


void RenderEngine::DestroyRenderWindow(IRenderWindow *Window)
{
	m_RenderWindows.Remove((RenderWindow*)Window);

	delete Window;
}


void RenderEngine::RenderCurrentScene(void)
{
	static const DWORD flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL;

	SetViewMatrix(m_CurrentCamera->GetViewMatrix());
	SetProjectionMatrix(m_CurrentCamera->GetProjectionMatrix());

	//D3DVIEWPORT9 viewport;
	//ZeroMemory(&viewport, sizeof(D3DVIEWPORT9));
	//viewport.X = 0;
	//viewport.Y = 0;
	//viewport.Width = 300;
	//viewport.Height = 300;
	//m_Device->SetViewport(&viewport);

	for (uint8 i = 0; i < m_MaxSupportedRenderTargetsCount; i++)
	{
		if (!m_SupportsMRT && !m_CurrentRenderTargets[i])
			continue;

		m_Device->SetRenderTarget(0, ((RenderTarget*)m_CurrentRenderTargets[i])->GetSurface()->GetNativeSurface());

		m_Device->Clear(0, NULL, flags, m_CurrentCamera->GetClearColour().Value, 1.0F, 0);

		m_CurrentScene->Render();

		if (m_SupportsMRT)
			break;
	}
}


RenderTargetView *RenderEngine::CreateRenderTargetView(void)
{
	RenderTargetView *rt = new RenderTargetView;

	m_RenderTargets.Add(rt);

	return rt;
}


void RenderEngine::DestroyRenderTargetView(RenderTargetView *RenderTargetView)
{
	m_RenderTargets.Remove(RenderTargetView);

	delete RenderTargetView;
}


void RenderEngine::SetRenderTargetStage(uint8 Stage, IRenderTarget *Target)
{
	ASSERTION(Stage < m_MaxSupportedRenderTargetsCount, "Current VideoCard supports only " + StringConverter::ToString(m_MaxSupportedRenderTargetsCount) + " Render Targets, but you trying to set more than this")

		IDirect3DSurface9 *surface = Target ? ((RenderTarget*)Target)->GetSurface()->GetNativeSurface() : NULL;

	if (m_CurrentRenderTargets[Stage] == Target &&
		m_CurrentRenderTargets[Stage] &&
		((RenderTarget*)m_CurrentRenderTargets[Stage])->GetSurface()->GetNativeSurface() == surface)
		return;
	else
		m_CurrentRenderTargets[Stage] = Target;

	if (m_SupportsMRT || Stage == 0)
		m_Device->SetRenderTarget(Stage, surface);

	//if (Target)
	//	m_Device->SetRenderTarget(Stage, surface);
	//else
	//	m_Device->SetRenderTarget(Stage, NULL);
}


void RenderEngine::SetPass(IPass *Pass)
{
	if (m_CurrentFillMode != Pass->GetFillMode())
	{
		m_CurrentFillMode = Pass->GetFillMode();

		switch (m_CurrentFillMode)
		{
		case FillModes::Point:
			m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT);
			break;
		case FillModes::Wireframe:
			m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			break;
		case FillModes::Solid:
			m_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			break;
		}
	}

	if (m_CurrentZCompareFunction != Pass->GetZCompareFunction())
	{
		m_CurrentZCompareFunction = Pass->GetZCompareFunction();

		if (m_CurrentZCompareFunction == CompareFunctions::Never)
			m_Device->SetRenderState(D3DRS_ZENABLE, FALSE);
		else
		{
			m_Device->SetRenderState(D3DRS_ZENABLE, TRUE);

			m_Device->SetRenderState(D3DRS_ZFUNC, TO_CMPFUNC(m_CurrentZCompareFunction));
		}
	}

	if (m_CurrentZWrite != Pass->GetZWrite())
	{
		m_CurrentZWrite = Pass->GetZWrite();

		m_Device->SetRenderState(D3DRS_ZWRITEENABLE, m_CurrentZWrite);
	}

	if (m_CurrentBlendOperation != Pass->GetBlendOperation())
	{
		m_CurrentBlendOperation = Pass->GetBlendOperation();

		m_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, m_CurrentBlendOperation != BlendOperations::None);

		switch (m_CurrentBlendOperation)
		{
		case BlendOperations::Add:
			m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			break;
		case BlendOperations::Min:
			m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MIN);
			break;
		case BlendOperations::Max:
			m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MAX);
			break;
		case BlendOperations::Subtract:
			m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
			break;
		case BlendOperations::RevSubtract:
			m_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			break;
		}
	}

	if (m_CurrentSourceBlendFactor != Pass->GetSourceBlendFactor())
	{
		m_CurrentSourceBlendFactor = Pass->GetSourceBlendFactor();
		m_Device->SetRenderState(D3DRS_SRCBLEND, TO_BLEND(m_CurrentSourceBlendFactor));
	}

	if (m_CurrentDestinationBlendFactor != Pass->GetDestinationBlendFactor())
	{
		m_CurrentDestinationBlendFactor = Pass->GetDestinationBlendFactor();
		m_Device->SetRenderState(D3DRS_SRCBLEND, TO_BLEND(m_CurrentDestinationBlendFactor));
	}

	if (m_CurrentAlphaTestFunction != Pass->GetAlphaTestFunction())
	{
		m_CurrentAlphaTestFunction = Pass->GetAlphaTestFunction();

		if (m_CurrentAlphaTestFunction == CompareFunctions::Never)
			m_Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		else
		{
			m_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

			m_Device->SetRenderState(D3DRS_ALPHAFUNC, TO_CMPFUNC(m_CurrentAlphaTestFunction));
		}
	}

	if (m_CurrentAlphaTestReference != Pass->GetAlphaTestReference())
	{
		m_CurrentAlphaTestReference = Pass->GetAlphaTestReference();

		m_Device->SetRenderState(D3DRS_ALPHAREF, m_CurrentAlphaTestReference);
	}

	if (m_CurrentCullType != Pass->GetCullType())
	{
		m_CurrentCullType = Pass->GetCullType();

		switch (m_CurrentCullType)
		{
		case CullTypes::None:
			m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		case CullTypes::ClockWise:
			m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		case CullTypes::CoClockWise:
			m_Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
		}
	}

	for (uint8 i = 0; i < m_MaxSupportedTexturesCount; i++)
		SetTextureStage(i, Pass->GetTextureStage(i));

	GPUProgramUsage *usage = (GPUProgramUsage*)Pass->GetVertexProgram();
	if (m_CurrentVertexProgram != usage->GetProgram())
	{
		m_CurrentVertexProgram = (VertexGPUProgram*)usage->GetProgram();
		m_Device->SetVertexShader(m_CurrentVertexProgram ? m_CurrentVertexProgram->GetShader() : NULL);
	}

	if (m_CurrentVertexProgram)
		SetGPUProgramParams(usage);

	usage = (GPUProgramUsage*)Pass->GetFragmentProgram();
	if (m_CurrentFragmentProgram != usage->GetProgram())
	{
		m_CurrentFragmentProgram = (FragmentGPUProgram*)usage->GetProgram();
		m_Device->SetPixelShader(m_CurrentFragmentProgram ? m_CurrentFragmentProgram->GetShader() : NULL);
	}

	if (m_CurrentFragmentProgram)
		SetGPUProgramParams(usage);
}


void RenderEngine::SetTextureStage(const uint8 Stage, ITexture *Texture)
{
	ASSERTION(Stage < m_MaxSupportedTexturesCount, "Current VideoCard supports only " + StringConverter::ToString(m_MaxSupportedTexturesCount) + " Textures, but you trying to set more than this")

	if (m_CurrentTexutres[Stage] == Texture)
		return;

	m_CurrentTexutres[Stage] = Texture;

	if (Texture)
		m_Device->SetTexture(Stage, (dynamic_cast<::Texture*>(Texture))->GetNativeTexture());
	else
	{
		m_Device->SetTexture(Stage, NULL);
		m_Device->SetTextureStageState(Stage, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	}
}


void RenderEngine::SetVertexDeclaration(VertexDeclarations Declaration)
{
	DWORD fvf = TO_FVF(Declaration);

	for (uint8 i = 0; i < m_MaxSupportedTexturesCount; i++)
	{
		if (!m_CurrentTexutres[i])
			break;

		fvf |= D3DFVF_TEX1;
	}

	if (m_CurrentFVF == fvf)
		return;

	m_CurrentFVF = fvf;

	if (FAILED(m_Device->SetFVF(m_CurrentFVF)))
		LOG_ERROR("Could not set VertexDeclaration");
}


void RenderEngine::SetWorldMatrix(const Matrix4 &Matrix)
{
	m_GPUParams[GPUParamDefinition::WORLD_MATRIX] = Matrix;

	m_Device->SetTransform(D3DTS_WORLD, (D3DMATRIX*)((void*)Matrix.GetPointer()));
}


void RenderEngine::SetViewMatrix(const Matrix4 &Matrix)
{
	m_GPUParams[GPUParamDefinition::VIEW_MATRIX] = Matrix;

	m_Device->SetTransform(D3DTS_VIEW, (D3DMATRIX*)((void*)Matrix.GetPointer()));
}


void RenderEngine::SetProjectionMatrix(const Matrix4 &Matrix)
{
	m_GPUParams[GPUParamDefinition::PROJECTION_MATRIX] = Matrix;

	m_Device->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)((void*)Matrix.GetPointer()));
}


void RenderEngine::DrawRenderer(IRenderer *Renderer)
{
	ITransform *tr = Renderer->GetHolder()->GetTransform();

	if (!m_CurrentCamera->IsInFrustum(tr->GetPosition(), Renderer->GetMesh()->GetBoundingSphere().GetRadius()))
		return;

	static Matrix4 mat;

	mat = tr->GetWorldMatrix();
	SetWorldMatrix(mat);

	mat = m_CurrentCamera->GetViewProjectionMatrix() * mat;
	SetGPUParams(GPUParamDefinition::WORLDVIEWPROJECTION_MATRIX, mat);

	IMaterial *mtl = Renderer->GetMaterial();
	IMesh *mesh = Renderer->GetMesh();

	if (mtl)
		FOR_EACH(pass, mtl->GetPasses())
	{
			SetPass(&pass);

			DrawMesh(mesh);
		}
	else
	{
		SetPass(m_BaseMaterial.GetPass(0));

		DrawMesh(mesh);
	}
}


void RenderEngine::DrawMesh(const IMesh *Mesh)
{
	static const IMesh *lastRenderedMesh = NULL;
	static bool setBuffers;

	setBuffers = (Mesh != lastRenderedMesh);

	NAMESPACE::Mesh *mesh = (NAMESPACE::Mesh*)Mesh;

	primitivesCount += mesh->GetPrimitivesCount();

	if (setBuffers)
	{
		lastRenderedMesh = Mesh;

		if (mesh->GetPrimitivesCount() > m_MaxSupportedPrimitivesCount)
			THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "PrimitivesCount count ", "")

		if (mesh->GetVerticesCount() > 65536)
			THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "VerticesCount count ", "")

			m_Device->SetStreamSource(0, mesh->GetVertexBuffer(), 0, mesh->GetVertexStride());
	}

	SetRenderState(RenderStates::ThreeDimensional);

	SetVertexDeclaration(mesh->GetVertexDeclaration());

	IDirect3DIndexBuffer9 *indBuffer = mesh->GetIndexBuffer();

	D3DPRIMITIVETYPE primitiveType;

	switch (mesh->GetPrimitiveType())
	{
	case PrimitiveTypes::LineStrip:
		primitiveType = D3DPT_LINESTRIP;
		break;
	case PrimitiveTypes::LineLoop:
		primitiveType = D3DPT_LINESTRIP;
		break;
	case PrimitiveTypes::Lines:
		break;
	case PrimitiveTypes::TriangleStrip:
		primitiveType = D3DPT_TRIANGLESTRIP;
		break;
	case PrimitiveTypes::TriangleFan:
		primitiveType = D3DPT_TRIANGLEFAN;
		break;
	case PrimitiveTypes::Triangles:
		primitiveType = D3DPT_TRIANGLELIST;
		break;
	case PrimitiveTypes::PointStrip:
	case PrimitiveTypes::Points:
		primitiveType = D3DPT_POINTLIST;
		break;
	}

	if (indBuffer)
	{
		if (setBuffers)
			m_Device->SetIndices(indBuffer);

		m_Device->DrawIndexedPrimitive(primitiveType, 0, 0, mesh->GetVerticesCount(), 0, mesh->GetPrimitivesCount());
	}
	else
		m_Device->DrawPrimitive(primitiveType, 0, mesh->GetPrimitivesCount());
}


void RenderEngine::DrawVerticesList(const Vertex *Vertices, uint32 VerticesCount, VertexDeclarations VertexDeclaration, const void *Indices, IndexDataAlignments IndexDataAlignment, uint32 PrimitivesCount, PrimitiveTypes PrimitiveType)
{
	if (PrimitivesCount > m_MaxSupportedPrimitivesCount)
		THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "PrimitivesCount count ", "")

	if (VerticesCount > 65536)
		THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "VerticesCount count ", "")

		SetRenderState(RenderStates::ThreeDimensional);

	SetVertexDeclaration(VertexDeclaration);

	const uint32 stridePitch = GET_FVF_STRIDE(VertexDeclaration);
	const D3DFORMAT indexType = TO_FMT(IndexDataAlignment);

	switch (PrimitiveType)
	{
	case PrimitiveTypes::LineStrip:
		m_Device->DrawIndexedPrimitiveUP(D3DPT_LINESTRIP, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);
		break;
	case PrimitiveTypes::LineLoop:
	{
								m_Device->DrawIndexedPrimitiveUP(D3DPT_LINESTRIP, 0, VerticesCount, PrimitivesCount - 1, Indices, indexType, Vertices, stridePitch);

								uint16 tmpIndices[] = { PrimitivesCount - 1, 0 };

								m_Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, VerticesCount, 1, tmpIndices, indexType, Vertices, stridePitch);
	} break;
	case PrimitiveTypes::Lines:
		m_Device->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);
		break;
	case PrimitiveTypes::TriangleStrip:
		m_Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);
		break;
	case PrimitiveTypes::TriangleFan:
		m_Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLEFAN, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);
		break;
	case PrimitiveTypes::Triangles:
		m_Device->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);
		break;
		//case PrimitiveTypes::POINT_SPRITES:
		//case PrimitiveTypes::POINTS:
		//	const float32 tmp = Material.Thickness / getScreenSize().Height;
		//	if (PrimitiveType == PT_POINT_SPRITES)
		//		m_Device->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		//	m_Device->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
		//	m_Device->SetRenderState(D3DRS_POINTSIZE, F2DW(tmp));
		//	tmp = 1.0f;
		//	m_Device->SetRenderState(D3DRS_POINTSCALE_A, F2DW(tmp));
		//	m_Device->SetRenderState(D3DRS_POINTSCALE_B, F2DW(tmp));
		//	m_Device->SetRenderState(D3DRS_POINTSIZE_MIN, F2DW(tmp));
		//	tmp = 0.0f;
		//	m_Device->SetRenderState(D3DRS_POINTSCALE_C, F2DW(tmp));

		//	m_Device->DrawIndexedPrimitiveUP(D3DPT_POINTLIST, 0, VerticesCount, PrimitivesCount, Indices, indexType, Vertices, stridePitch);

		//	m_Device->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
		//	if (pType == scene::EPT_POINT_SPRITES)
		//		m_Device->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
		//	break;
	}
}


void RenderEngine::DrawLine(const Vector3 &Start, const Vector3 &End, const Colour &Colour)
{
	//SetPass(BASE_MATERIAL.GetPass(0));

	//m_Driver->draw3DLine(TO_Vector3F(Start), TO_Vector3F(End), TO_SColor(Colour));
}


void RenderEngine::Draw2DTexture(const ITexture *Texture, const Vector2 &Destination, bool UseTransparency, const Colour &Colour)
{

}


#ifdef _DEBUG
void RenderEngine::GetAdapterInfo(uint32 DisplayAdapter)
{
	D3DADAPTER_IDENTIFIER9 dai;
	m_Direct3D->GetAdapterIdentifier(DisplayAdapter, 0, &dai);

	const int32 Product = HIWORD(dai.DriverVersion.HighPart),
		Version = LOWORD(dai.DriverVersion.HighPart),
		SubVersion = HIWORD(dai.DriverVersion.LowPart),
		Build = LOWORD(dai.DriverVersion.LowPart);

	char temp[512];
	sprintf_s(temp, "%s %s %d.%d.%d.%d", dai.Description, dai.Driver, Product, Version, SubVersion, Build);

	LOG_INFO(temp)

		//// Assign vendor name based on vendor id.
		//VendorID = static_cast<u16>(dai.VendorId);
		//switch (dai.VendorId)
		//{
		//case 0x1002: VendorName = "ATI Technologies Inc."; break;
		//case 0x10DE: VendorName = "NVIDIA Corporation"; break;
		//case 0x102B: VendorName = "Matrox Electronic Systems Ltd."; break;
		//case 0x121A: VendorName = "3dfx Interactive Inc"; break;
		//case 0x5333: VendorName = "S3 Graphics Co., Ltd."; break;
		//case 0x8086: VendorName = "Intel Corporation"; break;
		//default: VendorName = "Unknown VendorId: "; VendorName += (u32)dai.VendorId; break;
		//}
}
#endif


void RenderEngine::SetRenderState(RenderStates State)
{
	if (m_RenderState == State)
		return;

	m_RenderState = State;

	if (m_RenderState == RenderStates::ThreeDimensional)
		m_Device->SetRenderState(D3DRS_SRGBWRITEENABLE, TRUE);
	else if (m_RenderState == RenderStates::TwoDimensional)
	{
		m_Device->SetRenderState(D3DRS_ZENABLE, FALSE);

		//bla bla blah
	}
}


void RenderEngine::SetGPUProgramParams(GPUProgramUsage *Usage)
{
	GPUProgram *program = (GPUProgram*)Usage->GetProgram();

	program->SetConstantsToDefault();

	const GPUProgramUsage::AutoParamMap &autoParams = Usage->GetAutoParams();
	FOR_EACH(key, autoParams)
	{
		const String &name = *key;
		const String &param = autoParams[name];

		ASSERTION(m_GPUParams.ContainsKey(param), "GPUParam [" + param + "] is wrong")

			program->SetConstant(name, m_GPUParams[param]);
	}

	const GPUProgramUsage::ParamMap &params = Usage->GetParams();
	FOR_EACH(key, params)
	{
		const String &name = *key;

		program->SetConstant(name, params[name]);
	}

	//Usage->ClearParams();
}


END_NAMESPACE
