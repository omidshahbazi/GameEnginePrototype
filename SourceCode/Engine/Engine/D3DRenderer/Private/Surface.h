// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SURFACE_H
#define SURFACE_H

#include <Public\Vector2.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class Surface
{
public:
	Surface(void);
	virtual ~Surface(void)
	{
		if (m_NativeSurface)
			m_NativeSurface->Release();
	}

	IDirect3DSurface9 *GetNativeSurface(void) const
	{
		return m_NativeSurface;
	}
	void SetNativeSurface(IDirect3DSurface9 *Surface);

	const Vector2 &GetSize(void) const
	{
		return m_Size;
	}

private:
	IDirect3DSurface9 *m_NativeSurface;
	Vector2 m_Size;
};

END_NAMESPACE
#endif // SURFACE_H
