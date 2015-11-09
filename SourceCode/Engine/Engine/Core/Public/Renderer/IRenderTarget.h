// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IRENDERTARGET_H
#define IRENDERTARGET_H

#include <Public\Renderer\ITexture.h>

BEGIN_NAMESPACE

class ICamera;

class IRenderTarget : public ITexture
{
public:
	virtual ~IRenderTarget(void) {}

	virtual ICamera *GetCamera(void) = 0;
	virtual void SetCamera(ICamera *Camera) = 0;
};

END_NAMESPACE
#endif // IRENDERTARGET_H
