// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERENGINE_H
#define RENDERENGINE_H
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Renderer\ITextureResourcesFactory.h>
#include <Public\Renderer\IMaterialResourcesFactory.h>
#include <Public\Renderer\IGPUProgramUsage.h>
#include <Public\Matrix4.h>
#include <Private\Material.h>
#include <Private\Pass.h>
#include <Private\RenderTargetView.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class GPUProgramUsage;
class Camera;
class RenderWindow;
class IScene;
class VertexGPUProgram;
class FragmentGPUProgram;

class RenderEngine : public IRenderEngine
{
private:
	enum class RenderStates
	{
		TwoDimensional = 0,
		ThreeDimensional
	};

public:
	RenderEngine(void);
	~RenderEngine(void);

private:
	void Install(void);
	const String &GetName(void) const
	{
		static String name = "DirectX 9.0 Render Engine";
		return name;
	}
	const String &GetVersion(void) const
	{
		static String version = "1.0.0.0";
		return version;
	}

	void Update(void);
	void Render(void);

	void Initialize(void);

	IRenderWindow *CreateRenderWindow(const String &Text);
	IRenderWindow *CreateRenderWindow(WindowUtility::WindowHandle WindowHandle);
	void DestroyRenderWindow(IRenderWindow *Window);

public:
	void RenderCurrentScene(void);

	RenderTargetView *CreateRenderTargetView(void);
	void DestroyRenderTargetView(RenderTargetView *RenderTargetView);

	void SetRenderTargetStage(uint8 Stage, IRenderTarget *Target);
	void SetPass(IPass *Pass);
	void SetTextureStage(uint8 Stage, ITexture *Texture);
	void SetVertexDeclaration(VertexDeclarations Declaration);

	void SetWorldMatrix(const Matrix4 &Matrix);
	void SetViewMatrix(const Matrix4 &Matrix);
	void SetProjectionMatrix(const Matrix4 &Matrix);

	void DrawRenderer(IRenderer *Renderer);
	void DrawMesh(const IMesh *Mesh);
	void DrawVerticesList(const Vertex *Vertices, uint32 VerticesCount, VertexDeclarations VertexDeclaration, const void *Indices, IndexDataAlignments IndexDataAlignment, uint32 PrimitivesCount, PrimitiveTypes PrimitiveType);

	void DrawLine(const Vector3 &Start, const Vector3 &End, const Colour &Colour);
	void Draw2DTexture(const ITexture *Texture, const Vector2 &Destination, bool UseTransparency = false, const Colour &Colour = Colour::WHITE);

	const uint8 GetMaxSupportedRenderTargetsCount(void) const
	{
		return m_MaxSupportedRenderTargetsCount;
	}

	const uint32 GetMaxSupportedPrimitivesCount(void) const
	{
		return m_MaxSupportedPrimitivesCount;
	}

	const uint8 GetMaxSupportedTexturesCount(void) const
	{
		return m_MaxSupportedTexturesCount;
	}

	INLINE void SetGPUParams(const String &Name, bool Value)
	{
		m_GPUParams[Name] = Value;
	}
	INLINE void SetGPUParams(const String &Name, int32 Value)
	{
		m_GPUParams[Name] = Value;
	}
	INLINE void SetGPUParams(const String &Name, float32 Value)
	{
		m_GPUParams[Name] = Value;
	}
	INLINE void SetGPUParams(const String &Name, const Vector2 &Value)
	{
		m_GPUParams[Name] = Value;
	}
	INLINE void SetGPUParams(const String &Name, const Vector3 &Value)
	{
		m_GPUParams[Name] = Value;
	}
	INLINE void SetGPUParams(const String &Name, const Matrix4 &Value)
	{
		m_GPUParams[Name] = Value;
	}

	IDirect3DDevice9 *GetDevice(void) const
	{
		return m_Device;
	}

	const D3DPRESENT_PARAMETERS *GetPresentParameters(void) const
	{
		return &m_PresentParameters;
	}

	void AddRenderTarget(IRenderTarget *rt)
	{
		m_RenderTargets.Add(rt);
	}

private:
	void GetAdapterInfo(uint32 DisplayAdapter);
	void SetRenderState(RenderStates State);
	void SetGPUProgramParams(GPUProgramUsage *Usage);

private:
	typedef IRenderTarget* RenderTargetPointer;
	typedef Vector<RenderTargetPointer> RenderTargetsList;
	typedef Vector<ICamera*> CamerasList;
	typedef Vector<RenderWindow*> RenderWindowsList;

	IDirect3D9 *m_Direct3D;
	IDirect3DDevice9 *m_Device;
	D3DPRESENT_PARAMETERS m_PresentParameters;

	uint8 m_MaxSupportedRenderTargetsCount;
	uint32 m_MaxSupportedPrimitivesCount;
	uint8 m_MaxSupportedTexturesCount;

	RenderTargetsList m_RenderTargets;
	RenderWindowsList m_RenderWindows;

	Material m_BaseMaterial;

	IScene *m_CurrentScene;
	Camera *m_CurrentCamera;
	RenderTargetPointer *m_CurrentRenderTargets;
	RenderStates m_RenderState;
	DWORD m_CurrentFVF;
	FillModes m_CurrentFillMode;
	CompareFunctions m_CurrentZCompareFunction;
	bool m_CurrentZWrite;
	BlendOperations m_CurrentBlendOperation;
	BlendFactors m_CurrentSourceBlendFactor;
	BlendFactors m_CurrentDestinationBlendFactor;
	CompareFunctions m_CurrentAlphaTestFunction;
	uint8 m_CurrentAlphaTestReference;
	CullTypes m_CurrentCullType;
	Pass::TexturePointer *m_CurrentTexutres;
	VertexGPUProgram *m_CurrentVertexProgram;
	FragmentGPUProgram *m_CurrentFragmentProgram;
	IGPUProgramUsage::ParamMap m_GPUParams;

	//
	// For rendering on MRT problem, for a while I render foreach render target, set each one as first render target, then render everything what is nessesary
	//
	bool m_SupportsMRT;
};

END_NAMESPACE
#endif // RENDERENGINE_H
