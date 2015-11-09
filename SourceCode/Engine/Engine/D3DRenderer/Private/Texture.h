// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TEXTURE_H
#define TEXTURE_H

#include <Public\Image.h>
#include <Public\Renderer\ITexture.h>
#include <Public\Vector2.h>
#include <Private\Surface.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class RenderEngine;

class Texture : public ITexture
{
public:
	Texture(void) :
		m_NativeTexture(NULL),
		m_Levels(0),
		m_Surfaces(NULL)
	{
	}
	Texture(Image *Image, uint8 LevelsCount);
	Texture(const Vector2 &Size, ColourFormats Format);
	virtual ~Texture(void);

	const Vector2 &GetSize(void) const
	{
		return m_Surfaces[0]->GetSize();
	}
	void SetSize(const Vector2 &Size);
	
	IDirect3DTexture9 *GetNativeTexture(void) const
	{
		return m_NativeTexture;
	}
	void SetNativeTexture(IDirect3DTexture9 *NativeTexture);

	uint8 GetLevels(void) const
	{
		return m_Levels;
	}

	Surface *GetSurface(uint8 Level = 0)
	{
		ASSERTION(Level < m_Levels, "Level must be less than levels count")

		return m_Surfaces[Level];
	}

private:
	typedef Surface* SurfacePointer;

	IDirect3DTexture9 *m_NativeTexture;
	uint8 m_Levels;
	ColourFormats m_Format;
	SurfacePointer *m_Surfaces;
};

END_NAMESPACE
#endif // TEXTURE_H
