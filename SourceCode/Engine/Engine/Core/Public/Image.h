// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMAGE_H
#define IMAGE_H

#include <Public\ReferenceCounted.h>
#include <Public\Colour.h>
#include <Public\Vector2.h>

BEGIN_NAMESPACE

class CORE_API Image : public ReferenceCounted
{
public:
	Image(void);
	Image(uint32 Width, uint32 Height, uint32 BPP = 32);
	Image(const Vector2 &Size, uint32 BPP = 32);
	~Image(void);

	bool Load(const String &Path);
	void Save(const String &Path);

	void Clear(const Colour &Colour = Colour::BLACK);

	void DrawRectangle(const Vector2 &Origin, const Vector2 &Size, const Colour &Colour);
	
	void SetPixel(uint32 X, uint32 Y, const Colour &Colour);
	void SetPixel(const Vector2 &Position, const Colour &Colour);

	const Colour GetPixel(uint32 X, uint32 Y);
	const Colour GetPixel(const Vector2 &Position);

	Image *ConvertTo32Bit(void) const;

	void *GetData(void);
	const void *GetData(void) const;

	INLINE const Vector2 &GetSize(void) const
	{
		return m_Size;
	}

	INLINE uint32 GetBPP(void) const
	{
		return m_BPP;
	}

private:
	void *m_Data;
	Vector2 m_Size;
	uint32 m_BPP;
};

END_NAMESPACE
#endif // IMAGE_H
