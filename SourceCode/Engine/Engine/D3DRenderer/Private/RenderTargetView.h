// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERTARGETVIEW_H
#define RENDERTARGETVIEW_H

#include <Private\RenderTarget.h>

BEGIN_NAMESPACE

class RenderTargetView : public RenderTarget, public Surface
{
public:
	RenderTargetView(void)
	{
	}
	RenderTargetView(IDirect3DSurface9 *Surface)
	{
		SetNativeSurface(Surface);
	}
	virtual ~RenderTargetView(void) {}

	const Vector2 &GetSize(void) const
	{
		return Surface::GetSize();
	}

	Surface *GetSurface(void)
	{
		return this;
	}
};

END_NAMESPACE
#endif // RENDERTARGETVIEW_H
