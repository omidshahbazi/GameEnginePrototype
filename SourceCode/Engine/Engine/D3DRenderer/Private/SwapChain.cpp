// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\SwapChain.h>
#include <Private\RenderEngine.h>
#include <Private\RenderWindow.h>
#include <Public\Core.h>
#include <Public\Renderer\ICamera.h>

BEGIN_NAMESPACE


SwapChain::SwapChain(RenderWindow *Window) :
m_Window(Window),
m_NativeSwapChain(NULL),
m_RenderTarget(NULL)
{
	static RenderEngine *engine = (RenderEngine*)Core::GetReference().GetRenderer();
	m_RenderTarget = (RenderTargetView*)engine->CreateRenderTargetView();

	Reset();
}


SwapChain::~SwapChain(void)
{
	static RenderEngine *engine = (RenderEngine*)Core::GetReference().GetRenderer();
	engine->DestroyRenderTargetView(m_RenderTarget);

	if (m_NativeSwapChain)
		m_NativeSwapChain->Release();
}


void SwapChain::Reset(void)
{
	if (m_NativeSwapChain)
	{
		m_NativeSwapChain->Release();
		m_RenderTarget->SetNativeSurface(NULL);

		m_NativeSwapChain = NULL;
	}

	const Vector2 &size = m_Window->GetSize();

	if (size.X == 0.0F || size.Y == 0.0F)
		return;

	static RenderEngine *engine = (RenderEngine*)Core::GetReference().GetRenderer();
	static IDirect3DDevice9 *device = engine->GetDevice();

	D3DPRESENT_PARAMETERS params = *engine->GetPresentParameters();
	params.BackBufferWidth = (uint32)size.X;
	params.BackBufferHeight = (uint32)size.Y;
	params.Windowed = !m_Window->GetFullScreen();

	device->CreateAdditionalSwapChain(&params, &m_NativeSwapChain);

	IDirect3DSurface9 *surface;
	m_NativeSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surface);
	m_RenderTarget->SetNativeSurface(surface);
	surface->Release();
}


void SwapChain::Present(void)
{
	if (m_NativeSwapChain)
		m_NativeSwapChain->Present(NULL, NULL, m_Window->GetHandle(), NULL, 0);

	//D3DXSaveSurfaceToFile("D:/1.png", D3DXIFF_PNG, m_RenderTarget->GetNativeSurface(), NULL, NULL);
}


END_NAMESPACE
