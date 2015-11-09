// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Helper.h>
#include <Private\Font.h>

const char *SPECIAL_CHARACTERS("Qgqt{}[]");

BEGIN_NAMESPACE

void Helper::RenderText(const String &Text, IFont *Font, const Colour &Colour, Image *Image, const Vector2 Offset, bool Reverse)
{
	//#error Optimize This

	if (!Text.GetLength())
		return;
	String sentence = Text;
	FT_Glyph *glyphs = new FT_Glyph[sentence.GetLength()];
	FT_Vector *pos = new FT_Vector[sentence.GetLength()];

	FT_UInt32 glyph_index;
	FT_Bool use_kerning;
	FT_UInt32 previous;
	uint32 penX = 0, penY = 0;
	Vector2 StringDimensions = Vector2(0);

	NAMESPACE::Font *font = (NAMESPACE::Font*)Font;

	use_kerning = FT_HAS_KERNING(font->GetFace());

	sentence.Replace("\t", "    ");
	if (Reverse)
	{
		sentence.Reverse();
		penX = (uint32)Image->GetSize().X;
	}

	StringsList lines = sentence.Split("\n");

	uint32 glyphsCount;

	for (uint32 l = 0; l < lines.GetSize(); l++)
	{
		glyphsCount = 0;
		previous = 0;
		for (uint32 z = 0; z < lines[l].GetLength(); z++)
		{

			glyph_index = FT_Get_Char_Index(font->GetFace(), (int)lines[l][z]);

			if (use_kerning && previous && glyph_index)
			{
				FT_Vector delta;
				FT_Get_Kerning(font->GetFace(), previous, glyph_index, FT_KERNING_DEFAULT, &delta);
				if (Reverse)
					penX -= (delta.x >> 6) + 5;
				else
					penX += (delta.x >> 6) + 5;
			}

			pos[glyphsCount].x = penX;
			pos[glyphsCount].y = penY;

			FT_Load_Glyph(font->GetFace(), glyph_index, FT_LOAD_DEFAULT);

			FT_Get_Glyph(font->GetFace()->glyph, &glyphs[glyphsCount]);

			FT_GlyphSlot slot = font->GetFace()->glyph;


			if (Reverse)
				penX -= slot->advance.x >> 6;
			else
				penX += slot->advance.x >> 6;
			previous = glyph_index;

			glyphsCount++;
		}

		if (l == 0)
		{
			StringDimensions = CalculateStringDimensions(SPECIAL_CHARACTERS, font);
		}

		for (uint32 n = 0; n < glyphsCount; n++)
		{

			FT_Glyph_To_Bitmap(&glyphs[n], FT_RENDER_MODE_NORMAL, &pos[n], 0);

			FT_BitmapGlyph bit = (FT_BitmapGlyph)glyphs[n];

			if ((pos[n].x + bit->bitmap.width) > Image->GetSize().X && !Reverse)
				break;

			if (Reverse)
			{
				for (int32 i = pos[n].x; i > (pos[n].x - bit->bitmap.width); i--)
				for (int32 j = ((int)StringDimensions.Y - bit->top); j < ((int)StringDimensions.Y + bit->bitmap.rows - bit->top); j++)
				{
					const uint32 color = (bit->bitmap.buffer[(i - pos[n].x - 1) + bit->bitmap.width * (j - ((int)StringDimensions.Y - bit->top) + 1)] << 24) | Colour.Value;
					const uint32 a = color >> 24;

					if (a != 0)
						Image->SetPixel(uint32(i - Offset.X), uint32(j + Offset.Y), NAMESPACE::Colour(color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff, a));
				}
			}
			else
			{
				for (int32 i = pos[n].x; i < (pos[n].x + bit->bitmap.width); i++)
				for (int32 j = ((int)StringDimensions.Y - bit->top); j < ((int)StringDimensions.Y + bit->bitmap.rows - bit->top); j++)
				{
					const uint32 color = (bit->bitmap.buffer[(i - pos[n].x) + bit->bitmap.width * (j - ((int)StringDimensions.Y - bit->top))] << 24) | Colour.Value;
					const uint32 a = color >> 24;

					if (a != 0)
						Image->SetPixel(uint32(i + Offset.X), uint32(j + Offset.Y), NAMESPACE::Colour(color & 0xff, (color >> 8) & 0xff, (color >> 16) & 0xff, a));
				}
			}
		}

		penY = (int)StringDimensions.Y;
		StringDimensions.Y = (StringDimensions.Y * 2) + font->GetNewLineRatio();
		penX = 0;
	}
}


void Helper::MeasureStringBounding(FT_BBox *BoundingBox, FT_Glyph *Glyphs, FT_Vector *Positions, uint32 Count)
{
	FT_BBox box;
	FT_BBox glyphBox;

	box.xMin = box.yMin = 32000;
	box.xMax = box.yMax = -32000;

	for (uint32 i = 0; i < Count; i++)
	{
		FT_Glyph_Get_CBox(Glyphs[i], ft_glyph_bbox_pixels, &glyphBox);

		glyphBox.xMin += Positions[i].x;
		glyphBox.xMax += Positions[i].x;
		glyphBox.yMin += Positions[i].y;
		glyphBox.yMax += Positions[i].y;

		if (glyphBox.xMin < box.xMin)
			box.xMin = glyphBox.xMin;

		if (glyphBox.yMin < box.yMin)
			box.yMin = glyphBox.yMin;

		if (glyphBox.xMax > box.xMax)
			box.xMax = glyphBox.xMax;

		if (glyphBox.yMax > box.yMax)
			box.yMax = glyphBox.yMax;
	}

	if (box.xMin > box.xMax)
	{
		box.xMin = 0;
		box.yMin = 0;
		box.xMax = 0;
		box.yMax = 0;
	}

	*BoundingBox = box;
}


Vector2 Helper::CalculateStringDimensions(const String &Text, IFont *Font)
{
	FT_Glyph *glyphs = new FT_Glyph[Text.GetLength()];
	FT_Vector *pos = new FT_Vector[Text.GetLength()];

	FT_UInt32 glyph_index;
	FT_Bool use_kerning;
	FT_UInt32 previous = 0;
	uint32 penX = 0, penY = 0;

	NAMESPACE::Font *font = (NAMESPACE::Font*)Font;

	use_kerning = FT_HAS_KERNING(font->GetFace());

	uint32 glyphsCount = 0;

	for (uint32 z = 0; z < Text.GetLength(); z++)
	{

		glyph_index = FT_Get_Char_Index(font->GetFace(), (int)Text[z]);

		if (use_kerning && previous && glyph_index)
		{
			FT_Vector delta;
			FT_Get_Kerning(font->GetFace(), previous, glyph_index, FT_KERNING_DEFAULT, &delta);
			penX += delta.x >> 6;
		}

		pos[glyphsCount].x = penX;
		pos[glyphsCount].y = penY;

		FT_Load_Glyph(font->GetFace(), glyph_index, FT_LOAD_DEFAULT);

		FT_Get_Glyph(font->GetFace()->glyph, &glyphs[glyphsCount]);

		FT_GlyphSlot slot = font->GetFace()->glyph;


		penX += slot->advance.x >> 6;
		previous = glyph_index;

		glyphsCount++;
	}
	FT_BBox stringBbox;

	MeasureStringBounding(&stringBbox, glyphs, pos, glyphsCount);

	return Vector2(float32(stringBbox.xMax - stringBbox.xMin), float32(stringBbox.yMax - stringBbox.yMin));
}


END_NAMESPACE
