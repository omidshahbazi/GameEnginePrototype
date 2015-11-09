// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include <Public\Renderer\IRenderTarget.h>
#include <Private\Surface.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class RenderTarget : public IRenderTarget
{
public:
	RenderTarget(void) :
		m_Camera(NULL)
	{
	}
	virtual ~RenderTarget(void) {}

	virtual Surface *GetSurface(void) = 0;

	ICamera *GetCamera(void)
	{
		return m_Camera;
	}
	void SetCamera(ICamera *Camera)
	{
		m_Camera = Camera;
	}

private:
	ICamera *m_Camera;
};

END_NAMESPACE
#endif // RENDERTARGET_H
