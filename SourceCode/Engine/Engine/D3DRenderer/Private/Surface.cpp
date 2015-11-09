// Copyright 2012-2015 ?????????????. All Rights Reserved.

#include <Private\Surface.h>

BEGIN_NAMESPACE


Surface::Surface(void) :
m_NativeSurface(NULL)
{
}


void Surface::SetNativeSurface(IDirect3DSurface9 *Surface)
{
	if (m_NativeSurface == Surface)
		return;

	if (m_NativeSurface)
		m_NativeSurface->Release();

	m_NativeSurface = Surface;

	if (m_NativeSurface)
	{
		m_NativeSurface->AddRef();

		D3DSURFACE_DESC desc;
		m_NativeSurface->GetDesc(&desc);
		m_Size.X = (float32)desc.Width;
		m_Size.Y = (float32)desc.Height;
	}
}


END_NAMESPACE
