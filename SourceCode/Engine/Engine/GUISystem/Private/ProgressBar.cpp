// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ProgressBar.h>
#include <Public\Core.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Colour.h>
#include <Private\GUIScene.h>
#include <Private\Font.h>
#include <Private\Helper.h>
#include <Public\StringConverter.h>
#include <Public\CTime.h>

BEGIN_NAMESPACE

ProgressBar::ProgressBar(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font):
	m_Renderer(Core::GetReference().GetRenderer()),
	m_Input(Core::GetReference().GetInputManager()),
	m_Holder(Holder),
	m_UniqueName(((GUIScene*)m_Holder)->GetUniqeName()),
	m_BarImage(NULL),
	m_Texture(NULL),
	m_BarColour(Colour(0, 0, 200)),
	m_IsDirty(false),
	m_DisplayText(true)
{
	SetSize(Size);
	SetName(Name);

	//m_Image = m_Renderer->CreateImage(m_UniqueName, GetSize());
	
	SetForeColour(Colour::WHITE);
	SetBackColour(Colour::BLACK);
	SetFont(Font);
	SetBorderColour(Colour::BLACK);
	SetBorderSize(1);
}


ProgressBar::~ProgressBar(void)
{
}

void ProgressBar::Update(void)
{
	//SetPrecent(++m_Precent);
	if (m_IsDirty)
	{
		m_IsDirty = false;

		UpdateData();
	}
}

void ProgressBar::Render(void)
{
	m_Renderer->Draw2DTexture(m_Texture, GetLocation(), true);	
}


void ProgressBar::SetFont(IFont *Font)
{
	if (Font && GetFont() == Font)
		return;

	IProgressBar::SetFont(Font);

	m_IsDirty = true;
}


void ProgressBar::SetForeColour(const Colour &Colour)
{
	if (Colour == GetForeColour())
		return;

	IProgressBar::SetForeColour(Colour);

	m_IsDirty = true;
}


void ProgressBar::SetBackColour(const Colour &Colour)
{
	if (Colour == GetBackColour())
		return;

	IProgressBar::SetBackColour(Colour);

	m_IsDirty = true;
}


void ProgressBar::SetPrecent(float32 Precent)
{
	if (Precent < 0)
		m_Precent = 0;
	if (Precent > 100)
		m_Precent = 100;
	else
		m_Precent = Precent;
	m_IsDirty = true;
}


void ProgressBar::SetBarColour(const Colour &Colour)
{
	if (m_BarColour == Colour)
		return;

	m_BarColour = Colour;
	m_IsDirty = true;
}


void ProgressBar::SetDisplayText(bool DisplayText)
{
	m_DisplayText = DisplayText;
}


void ProgressBar::UpdateData(void)
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


	if (m_BarImage)
	{
		for (uint32 i = borderSize; i < ((m_Precent * GetSize().X) / 100) - borderSize; i++)
			for (uint32 j = borderSize; j < GetSize().Y - borderSize; j++)
				if(i - borderSize < m_BarImage->GetSize().X && j - borderSize < m_BarImage->GetSize().Y)
					m_Image->SetPixel(i, j, m_BarImage->GetPixel(Vector2(float32(i - borderSize), float32(j - borderSize))));
				else
					m_Image->SetPixel(i, j, GetBackColour());
	}
	else
	{
		m_Image->DrawRectangle(origin, Vector2(((m_Precent * GetSize().X) / 100) - origin.X, GetSize().Y - origin.Y), m_BarColour);
	}

	Vector2 stringDimensions = Helper::CalculateStringDimensions(StringConverter::ToString(m_Precent), GetFont());
	if (m_DisplayText)
		Helper::RenderText(StringConverter::ToString(m_Precent) + "%", GetFont(), GetForeColour(), m_Image, Vector2(((m_Image->GetSize().X - borderSize + 2) / 2.0F) - (stringDimensions.X / 2.0F), ((m_Image->GetSize().Y - borderSize + 2) / 2.0F) - (stringDimensions.Y / 2.0F)));

	if (m_Texture)
		m_Texture->Drop();

	m_Texture = TextureResourcesManager::GetReference().CreateTexture(m_UniqueName, m_Image);

}


END_NAMESPACE
