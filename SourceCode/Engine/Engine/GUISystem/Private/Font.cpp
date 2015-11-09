// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Font.h>


BEGIN_NAMESPACE


Font::Font(const String &Name, uint32 Size, FT_Face Face) :
	m_Name(Name),
	m_Face(Face)
{
	SetSize(Size);
	SetNewLineRatio(0);
}


Font::~Font(void)
{
	FT_Done_Face(m_Face);

	LOG_INFO_DEBUG("IFont [" + m_Name + "] destoryed successfully")
}


void Font::SetSize(uint32 Size)
{
	if (m_Size == Size)
		return;

	m_Size = Size;

	FT_Set_Char_Size(m_Face, 0, m_Size * 64, 0, 0);
}

END_NAMESPACE
