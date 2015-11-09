// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FONT_H
#define FONT_H

#include <Public\GUISystem\IFont.h>
#include <Private\FreeTypeInclude.h>

BEGIN_NAMESPACE

class Font : public IFont
{
public:
	Font(const String &Name, uint32 Size, FT_Face Face);
	~Font(void);

	FT_Face GetFace(void)
	{
		return m_Face;
	}
	
	const String &GetName(void) const
	{
		return m_Name;
	}

	void SetSize(uint32 Size);
	uint32 GetSize(void) const
	{
		return m_Size;
	}
	
	void SetNewLineRatio(float32 Ratio)
	{
		if (Ratio == 0)
			m_NewLineRatio = (m_Size * 20.f / 80.f);
		else
			m_NewLineRatio = Ratio;
	}
	float32 GetNewLineRatio(void) const
	{
		return m_NewLineRatio;
	}

private:
	FT_Face m_Face;
	String m_Name;
	uint32 m_Size;
	float32 m_NewLineRatio;
};

END_NAMESPACE
#endif // FONT_H
