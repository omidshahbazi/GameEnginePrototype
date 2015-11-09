// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <Public\Renderer\IRenderWindow.h>

BEGIN_NAMESPACE

class SwapChain;

class RenderWindow : public IRenderWindow
{
public:
	RenderWindow(WindowUtility::WindowHandle Handle) :
		IRenderWindow(Handle),
		m_SwapChain(NULL)
	{
		UpdateSwapChain();
	}
	RenderWindow(const String &Text) :
		IRenderWindow(Text),
		m_SwapChain(NULL)
	{
		UpdateSwapChain();
	}
	virtual ~RenderWindow(void);

	ICamera *GetCamera(void) const;
	void SetCamera(ICamera *Camera);

	void Present(void);

private:
	void UpdateSizeChanges(void);
	void OnSizeChanged(const Vector2 &Size);
	void OnClose(void);

	void UpdateSwapChain(void);

private:
	SwapChain *m_SwapChain;
};

END_NAMESPACE
#endif // RENDERWINDOW_H
