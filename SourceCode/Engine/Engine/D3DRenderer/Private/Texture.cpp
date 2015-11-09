// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Texture.h>
#include <Private\RenderEngine.h>
#include <Private\RendererCommon.h>
#include <Public\Core.h>

BEGIN_NAMESPACE


Texture::Texture(Image *Image, uint8 LevelsCount) :
m_NativeTexture(NULL),
m_Levels(0),
m_Surfaces(NULL)
{
	static IDirect3DDevice9 *device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	const Vector2 &size = Image->GetSize();

	if (Image->GetBPP() < 32)
		Image = Image->ConvertTo32Bit();

	IDirect3DTexture9 *texture = NULL;

	device->CreateTexture((uint32)size.X, (uint32)size.Y, LevelsCount, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, 0);

	if (!texture)
	{
		Drop();
		return;
	}

	D3DLOCKED_RECT rect;
	texture->LockRect(0, &rect, 0, D3DLOCK_NOSYSLOCK);

	uint8 *dest = (uint8*)rect.pBits;
	uint8 *source = (uint8*)Image->GetData() + (((uint32)size.Y - 1) * rect.Pitch);

	for (uint16 y = 0; y < size.Y; y++)
	{
		memcpy(dest, source, rect.Pitch);

		dest += rect.Pitch;
		source -= rect.Pitch;
	}

	texture->UnlockRect(0);

	SetNativeTexture(texture);
}


Texture::Texture(const Vector2 &Size, ColourFormats Format) :
m_NativeTexture(NULL),
m_Levels(0),
m_Format(Format),
m_Surfaces(NULL)
{
	SetSize(Size);
}


Texture::~Texture(void)
{
	if (m_NativeTexture)
	{
		m_NativeTexture->Release();

		delete[] m_Surfaces;
	}
}


void Texture::SetSize(const Vector2 &Size)
{
	if (Size == Vector2::ZERO || (m_Surfaces && m_Surfaces[0]->GetSize() == Size))
		return;

	static IDirect3DDevice9 *device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	IDirect3DTexture9 *texture = NULL;

	device->CreateTexture((uint32)Size.X, (uint32)Size.Y, 1, D3DUSAGE_RENDERTARGET, TO_D3DFORMAT(m_Format), D3DPOOL_DEFAULT, &texture, 0);

	if (!texture)
	{
		Drop();
		return;
	}

	SetNativeTexture(texture);
}


void Texture::SetNativeTexture(IDirect3DTexture9 *NativeTexture)
{
	if (m_NativeTexture)
	{
		m_NativeTexture->Release();
		delete[] m_Surfaces;
	}

	m_NativeTexture = NativeTexture;

	m_NativeTexture->AddRef();

	m_Levels = (uint8)m_NativeTexture->GetLevelCount();

	m_Surfaces = new SurfacePointer[m_Levels];

	IDirect3DSurface9 *nativeSurface = NULL;
	for (uint8 i = 0; i < m_Levels; i++)
	{
		m_NativeTexture->GetSurfaceLevel(i, &nativeSurface);
		m_Surfaces[i] = new Surface;
		m_Surfaces[i]->SetNativeSurface(nativeSurface);
	}
}


END_NAMESPACE
