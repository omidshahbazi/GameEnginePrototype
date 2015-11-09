// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\RenderWindow.h>
#include <Private\SwapChain.h>
#include <Public\Core.h>
#include <Public\Renderer\IRenderEngine.h>

BEGIN_NAMESPACE


RenderWindow::~RenderWindow(void)
{
	delete m_SwapChain;
}


ICamera *RenderWindow::GetCamera(void) const
{
	return m_SwapChain->GetRenderTarget()->GetCamera();
}


void RenderWindow::SetCamera(ICamera *Camera)
{
	m_SwapChain->GetRenderTarget()->SetCamera(Camera);
}


void RenderWindow::Present(void)
{
	m_SwapChain->Present();
}


void RenderWindow::UpdateSizeChanges(void)
{
	NativeWindow::UpdateSizeChanges();

	UpdateSwapChain();
}


void RenderWindow::OnSizeChanged(const Vector2 &Size)
{
	NativeWindow::OnSizeChanged(Size);

	UpdateSwapChain();
}


void RenderWindow::OnClose(void)
{
	static IRenderEngine *engine = Core::GetReference().GetRenderer();
	engine->DestroyRenderWindow(this);
}


void RenderWindow::UpdateSwapChain(void)
{
	if (m_SwapChain)
		m_SwapChain->Reset();
	else
		m_SwapChain = new SwapChain(this);
}

END_NAMESPACE
