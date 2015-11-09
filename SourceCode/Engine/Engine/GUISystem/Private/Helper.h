// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef HELPER_H
#define HELPER_H

#include <Public\Colour.h>
#include <Public\Image.h>
#include <Public\GUISystem\IFont.h>
#include <Private\FreeTypeInclude.h>

BEGIN_NAMESPACE

class Helper
{
public:

	static void RenderText(const String &Text, IFont *Font, const Colour &Colour, Image *Image, const Vector2 Offset = Vector2::ZERO, bool Reverse = false);

	static Vector2 CalculateStringDimensions(const String &Text, IFont *Font);

private:
	static void MeasureStringBounding(FT_BBox *BoundingBox, FT_Glyph *Glyphs, FT_Vector *Positions, uint32 Count);
};

END_NAMESPACE
#endif // HELPER_H
