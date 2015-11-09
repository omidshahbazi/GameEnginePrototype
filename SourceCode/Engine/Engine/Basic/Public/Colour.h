// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COLOUR_H
#define COLOUR_H

#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

REFLECTION_ENUM()
enum class ColourFormats
{
	// 16 bit color format used
	A1R5G5B5 = 0,

	// Standard 16 bit color format
	R5G6B5,

	// 24 bit color, no alpha channel, but 8 bit for red, green and blue
	R8G8B8,

	// Default 32 bit color format. 8 bits are used for every component: red, green, blue and alpha
	A8R8G8B8,

	// 16 bit floating point32 format using 16 bits for the red channel
	R16F,

	// 32 bit floating point32 format using 16 bits for the red channel and 16 bits for the green channel
	G16R16F,

	// 64 bit floating point32 format 16 bits are used for the red, green, blue and alpha channels
	A16B16G16R16F,

	// 32 bit floating point32 format using 32 bits for the red channel
	R32F,

	// 64 bit floating point32 format using 32 bits for the red channel and 32 bits for the green channel
	G32R32F,

	// 128 bit floating point32 format. 32 bits are used for the red, green, blue and alpha channels
	A32B32G32R32F
};

//<Description>
//This is sample description
struct BASIC_API Colour
{
public:
	INLINE static uint16 X8R8G8B8toA1R5G5B5(uint32 color)
	{
		return (uint16)(0x8000 |
			(color & 0x00F80000) >> 9 |
			(color & 0x0000F800) >> 6 |
			(color & 0x000000F8) >> 3);
	}

	INLINE static uint16 A8R8G8B8toA1R5G5B5(uint32 color)
	{
		return (uint16)((color & 0x80000000) >> 16 |
			(color & 0x00F80000) >> 9 |
			(color & 0x0000F800) >> 6 |
			(color & 0x000000F8) >> 3);
	}


	INLINE static uint16 A8R8G8B8toR5G6B5(uint32 color)
	{
		return (uint16)((color & 0x00F80000) >> 8 |
			(color & 0x0000FC00) >> 5 |
			(color & 0x000000F8) >> 3);
	}


	INLINE static uint32 A1R5G5B5toA8R8G8B8(uint16 color)
	{
		return (((-((int32)color & 0x00008000) >> (int32)31) & 0xFF000000) |
			((color & 0x00007C00) << 9) | ((color & 0x00007000) << 4) |
			((color & 0x000003E0) << 6) | ((color & 0x00000380) << 1) |
			((color & 0x0000001F) << 3) | ((color & 0x0000001C) >> 2)
			);
	}


	INLINE static uint32 R5G6B5toA8R8G8B8(uint16 color)
	{
		return 0xFF000000 |
			((color & 0xF800) << 8) |
			((color & 0x07E0) << 5) |
			((color & 0x001F) << 3);
	}


	INLINE static uint16 R5G6B5toA1R5G5B5(uint16 color)
	{
		return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
	}

	INLINE static uint16 A1R5G5B5toR5G6B5(uint16 color)
	{
		return (((color & 0x7FE0) << 1) | (color & 0x1F));
	}

public:
	INLINE Colour(void)
	{
		Set(0, 0, 0, 255);
	}
	INLINE Colour(uint8 Scalar)
	{
		Set(Scalar, Scalar, Scalar);
	}
	INLINE Colour(uint8 R, uint8 G, uint8 B, uint8 A = 255)
	{
		Set(R, G, B, A);
	}
	INLINE Colour(const Colour &Colour) :
		Value(Colour.Value)
	{
	}

	INLINE Colour &operator = (const Colour &Colour)
	{
		Value = Colour.Value;

		return *this;
	}

	INLINE bool operator == (const Colour &Colour) const
	{
		return Value == Colour.Value;
	}
	INLINE bool operator != (const Colour &Colour) const
	{
		return !this->operator==(Colour);
	}

	INLINE uint8 GetAlpha(void) const
	{
		return ((uint8*)&Value)[3];
	}
	INLINE void SetAlpha(uint8 Alpha)
	{
		((uint8*)&Value)[3] = Alpha;
	}
	INLINE uint8 GetRed(void) const
	{
		return ((uint8*)&Value)[2];
	}
	INLINE void SetRed(uint8 Red)
	{
		((uint8*)&Value)[2] = Red;
	}
	INLINE uint8 GetGreen(void) const
	{
		return ((uint8*)&Value)[1];
	}
	INLINE void SetGreen(uint8 Green)
	{
		((uint8*)&Value)[1] = Green;
	}
	INLINE uint8 GetBlue(void) const
	{
		return *(uint8*)&Value;
	}
	INLINE void SetBlue(uint8 Blue)
	{
		*((uint8*)&Value) = Blue;
	}

	INLINE void Set(uint8 R, uint8 G, uint8 B, uint8 A = 255)
	{
		uint8 *dest = (uint8*)&Value;
		dest[0] = B;
		dest[1] = G;
		dest[2] = R;
		dest[3] = A;
	}

	INLINE void Set(void *Data, ColourFormats Format = ColourFormats::A8R8G8B8)
	{
		switch (Format)
		{
		case ColourFormats::A1R5G5B5:
			Value = A1R5G5B5toA8R8G8B8(*(uint16*)Data);
			break;
		case ColourFormats::R5G6B5:
			Value = R5G6B5toA8R8G8B8(*(uint16*)Data);
			break;
		case ColourFormats::A8R8G8B8:
			Value = Value;
			break;
		case ColourFormats::R8G8B8:
		{
						 uint8 *p = (uint8*)Data;
						 Set(p[2], p[1], p[0], 255);
						 break;
		}
		default:
			Value = 0xFF000000;
			break;
		}
	}

	void Get(void *Data, ColourFormats Format) const
	{
		switch (Format)
		{
		case ColourFormats::A1R5G5B5:
		{
						   uint16 *dest = (uint16*)Data;
						   *dest = A8R8G8B8toA1R5G5B5(Value);
						   break;
		}
		case ColourFormats::R5G6B5:
		{
						 uint16 *dest = (uint16*)Data;
						 *dest = A8R8G8B8toR5G6B5(Value);
						 break;
		}
		case ColourFormats::R8G8B8:
		{
						 uint8 *dest = (uint8*)Data;
						 dest[2] = (uint8)GetRed();
						 dest[1] = (uint8)GetGreen();
						 dest[0] = (uint8)GetBlue();
						 break;

		}
		case ColourFormats::A8R8G8B8:
			*(uint32*)Data = Value;
			break;
		}
	}

public:
	// Colour in ARGB format
	uint32 Value;

	static const Colour BLACK;
	static const Colour WHITE;
	static const Colour RED;
	static const Colour GREEN;
	static const Colour BLUE;
	static const Colour CYAN;
	static const Colour YELLOW;
	static const Colour MAGENTA;
};

END_NAMESPACE
#endif // COLOUR_H
