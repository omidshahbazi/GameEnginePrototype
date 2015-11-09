// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Label.h>
#include <Public\Core.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Colour.h>
#include <Private\GUISystem.h>
#include <Private\GUIScene.h>
#include <Private\Font.h>
#include <Private\Helper.h>

USING_NAMESPACE


Label::Label(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font, const String &Text) :
	m_Renderer(Core::GetReference().GetRenderer()),
	m_Holder(Holder),
	m_UniqueName(((GUIScene*)m_Holder)->GetUniqeName()),
	m_Texture(NULL),
	m_IsDirty(false)
{
	SetSize(Size);
	SetName(Name);

	//m_Image = m_Renderer->CreateImage(m_UniqueName, GetSize());
	
	SetForeColour(Colour::WHITE);
	SetBackColour(Colour::BLACK);
	SetFont(Font);
	SetText(Text);
}


Label::~Label(void)
{
	//m_Renderer->DestroyImage(m_Image);
	m_Texture->Drop();

	LOG_INFO_DEBUG("ILabel destoryed successfully")
}


void Label::Render(void)
{
	if (m_IsDirty)
	{
		m_IsDirty = false;

		UpdateData();
	}

	m_Renderer->Draw2DTexture(m_Texture, GetLocation(), true);
}


void Label::SetFont(IFont *Font)
{
	if (Font && GetFont() == Font)
		return;

	ILabel::SetFont(Font);

	m_IsDirty = true;
}


void Label::SetForeColour(const Colour &Colour)
{
	if (Colour == GetForeColour())
		return;

	ILabel::SetForeColour(Colour);

	m_IsDirty = true;
}


void Label::SetBackColour(const Colour &Colour)
{
	if (Colour == GetBackColour())
		return;

	ILabel::SetBackColour(Colour);

	m_IsDirty = true;
}


void Label::SetOffset(const Vector2 &Offset)
{
	m_Offset = Offset;

	m_IsDirty = true;
}


void Label::SetText(const String &Text)
{
	if (m_Text == Text)
		return;

	m_Text = Text;

	m_IsDirty = true;
}


void Label::UpdateData(void)
{
	if (!GetFont())
		return;

	uint32 borderSize = GetBorderSize();

	if (borderSize)
		m_Image->Clear(GetBorderColour());

	const Vector2 origin((float32)borderSize);
	
	if (GetBackImage())
	{
		for (uint32 i = borderSize; i < GetSize().X - borderSize; i++)
			for (uint32 j = borderSize; j < GetSize().Y - borderSize; j++)
				if(i - borderSize < GetBackImage()->GetSize().X && j - borderSize < GetBackImage()->GetSize().Y)
					m_Image->SetPixel(i, j, GetBackImage()->GetPixel(Vector2(float32(i - borderSize), float32(j - borderSize))));
				else
					m_Image->SetPixel(i, j, GetBackColour());
	}
	else
	{
		m_Image->DrawRectangle(origin, GetSize() - origin, GetBackColour());
	}

	Vector2 stringDimensions = Helper::CalculateStringDimensions(m_Text, GetFont());

	Helper::RenderText(m_Text, GetFont(), GetForeColour(), m_Image, Vector2(((m_Image->GetSize().X - borderSize + 2) / 2.0F) - (stringDimensions.X / 2.0F) + m_Offset.X, ((m_Image->GetSize().Y - borderSize + 2) / 2.0F) - (stringDimensions.Y / 2.0F) + m_Offset.Y));

	if (m_Texture)
		m_Texture->Drop();

	m_Texture = TextureResourcesManager::GetReference().CreateTexture(m_UniqueName, m_Image);
}
