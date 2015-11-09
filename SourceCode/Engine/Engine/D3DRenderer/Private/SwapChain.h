// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H
#include <Public\SecondaryCommon.h>
#include <Private\DirectXInclude.h>
#include <Private\RenderTargetView.h>

BEGIN_NAMESPACE

class RenderWindow;
class ICamera;

class SwapChain
{
	friend class RenderWindow;

public:
	SwapChain(RenderWindow *Window);
	~SwapChain(void);

	void Reset(void);
	
	void Present(void);

	RenderTargetView *GetRenderTarget(void)
	{
		return m_RenderTarget;
	}

private:
	RenderWindow *m_Window;
	IDirect3DSwapChain9 *m_NativeSwapChain;
	RenderTargetView *m_RenderTarget;
};

END_NAMESPACE
#endif // SWAPCHAIN_H
