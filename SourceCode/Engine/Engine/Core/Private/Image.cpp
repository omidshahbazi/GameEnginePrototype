// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Image.h>
#include <Public\Core.h>
#include <Public\StringUtility.h>
#include <Private\FreeImageInclude.h>

BEGIN_NAMESPACE

static void output(FREE_IMAGE_FORMAT Format, const char *Message)
{
	LOG_ERROR(Message)
}


INLINE void Initiliaze(void)
{
	static bool initialized = false;

	if (!initialized)
	{
		initialized = false;

		FreeImage_Initialise(TRUE);

		FreeImage_SetOutputMessage(output);
	}
}


Image::Image(void)
{
	Initiliaze();
}


Image::Image(uint32 Width, uint32 Height, uint32 BPP) :
m_Size((float32)Width, (float32)Height),
m_BPP(BPP)
{
	Initiliaze();

	m_Data = FreeImage_Allocate((int32)m_Size.X, (int32)m_Size.Y, m_BPP, 4, 4, 4);
}


Image::Image(const Vector2 &Size, uint32 BPP) :
m_Size(Size),
m_BPP(BPP)
{
	Initiliaze();

	m_Data = FreeImage_Allocate((int32)m_Size.X, (int32)m_Size.Y, m_BPP, 4, 4, 4);
}


Image::~Image(void)
{
	if (m_Data)
		FreeImage_Unload((FIBITMAP*)m_Data);
}


bool Image::Load(const String &Path)
{
	const char *path = Path.GetBuffer();

	m_Data = FreeImage_Load(FreeImage_GetFIFFromFilename(path), path);

	if (m_Data == NULL)
		return false;

	FIBITMAP *bitmap = (FIBITMAP*)m_Data;

	m_Size.X = (float32)FreeImage_GetWidth(bitmap);
	m_Size.Y = (float32)FreeImage_GetHeight(bitmap);
	m_BPP = FreeImage_GetBPP(bitmap);

	return true;
}


void Image::Save(const String &Path)
{
	const char *path = Path.GetBuffer();

	FreeImage_Save(FreeImage_GetFIFFromFilename(path), (FIBITMAP*)m_Data, path);
}


void Image::Clear(const Colour &Colour)
{
	DrawRectangle(Vector2::ZERO, m_Size, Colour);
}


void Image::DrawRectangle(const Vector2 &Origin, const Vector2 &Size, const Colour &Colour)
{
	FIBITMAP *bitmap = (FIBITMAP*)m_Data;

	const uint32 flipY = (uint32)m_Size.Y - 1;

	RGBQUAD *colour = (RGBQUAD*)&Colour;

	for (float32 x = Origin.X; x < Size.X; x++)
	for (float32 y = Origin.Y; y < Size.Y; y++)
	{
		if (x >= m_Size.X || y >= m_Size.Y)
			return;

		FreeImage_SetPixelColor(bitmap, (uint32)x, uint32(flipY - y), colour);
	}
}


void Image::SetPixel(uint32 X, uint32 Y, const Colour &Colour)
{
	const uint32 flipY = (uint32)m_Size.Y - 1;

	FreeImage_SetPixelColor((FIBITMAP*)m_Data, X, flipY - Y, (RGBQUAD*)&Colour);
}


void Image::SetPixel(const Vector2 &Position, const Colour &Colour)
{
	SetPixel((uint32)Position.X, (uint32)Position.Y, Colour);
}


const Colour Image::GetPixel(uint32 X, uint32 Y)
{
	Colour colour;
	FreeImage_GetPixelColor((FIBITMAP*)m_Data, X, Y, (RGBQUAD*)&colour);
	return colour;
}


const Colour Image::GetPixel(const Vector2 &Position)
{
	return GetPixel((uint32)Position.X, (uint32)Position.Y);
}


Image *Image::ConvertTo32Bit(void) const
{
	Image *img = new Image;
	img->m_Data = FreeImage_ConvertTo32Bits((FIBITMAP*)m_Data);
	img->m_Size = m_Size;
	img->m_BPP = 32;
	return img;
}


void *Image::GetData(void)
{
	return FreeImage_GetBits((FIBITMAP*)m_Data);
}


const void *Image::GetData(void) const
{
	return ((FIBITMAP*)m_Data)->data;
}

END_NAMESPACE
