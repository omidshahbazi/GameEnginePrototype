// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Button.h>
#include <Public\Core.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Colour.h>
#include <Private\GUIScene.h>
#include <Private\Font.h>
#include <Private\Helper.h>
#include <Public\StringConverter.h>
#include <Public\CTime.h>

BEGIN_NAMESPACE

Button::Button(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font):
	m_Renderer(Core::GetReference().GetRenderer()),
	m_Input(Core::GetReference().GetInputManager()),
	m_Holder(Holder),
	m_UniqueName(((GUIScene*)m_Holder)->GetUniqeName()),
	m_Texture(NULL),
	m_MouseOverColour(GetBackColour()),
	m_MouseClickColour(GetBackColour()),
	m_IsDirty(false),
	m_Focus(false),
	m_Clicked(false),
	m_Over(false),
	m_Time(Time::GetReference().GetRealTime())
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


Button::~Button(void)
{
}

void Button::Update(void)
{
	if (m_Clicked && Time::GetReference().GetRealTime() - m_Time > 100)
	{
		m_Clicked = false;
		m_IsDirty = true;
	}
	
	const bool hover = IsMouseHover();
	if (hover != m_Over)
	{
		m_Over = hover;
		m_IsDirty = true;
	}

	if (m_Input->IsMouseClicked(IInputManager::M_LEFT))
	{
		if (hover)
		{
			m_Focus = true;
			m_Clicked = true;
			m_IsDirty = true;
			m_Time = Time::GetReference().GetRealTime();
		}
		else
			m_Focus = false;
	}

	if (m_IsDirty)
	{
		m_IsDirty = false;

		UpdateData();
	}
}

void Button::Render(void)
{
	m_Renderer->Draw2DTexture(m_Texture, GetLocation(), true);	
}


void Button::SetFont(IFont *Font)
{
	if (Font && GetFont() == Font)
		return;

	IButton::SetFont(Font);

	m_IsDirty = true;
}


void Button::SetForeColour(const Colour &Colour)
{
	if (Colour == GetForeColour())
		return;

	IButton::SetForeColour(Colour);

	m_IsDirty = true;
}


void Button::SetBackColour(const Colour &Colour)
{
	if (Colour == GetBackColour())
		return;

	IButton::SetBackColour(Colour);

	m_IsDirty = true;
}


void Button::SetCaption(const String &Text)
{
	m_Text = Text;
	m_IsDirty = true;
}


void Button::SetMouseOverColour(const Colour &Colour)
{
	if (m_MouseOverColour == Colour)
		return;

	m_MouseOverColour = Colour;
	m_IsDirty = true;
}


void Button::SetMouseClickColour(const Colour &Colour)
{
	if (m_MouseClickColour == Colour)
		return;

	m_MouseClickColour = Colour;
	m_IsDirty = true;
}


void Button::SetFocus(bool Focus)
{
	m_Focus = Focus;
}


void Button::UpdateData(void)
{
	if (!GetFont())
		return;
	uint32 bordersize = GetBorderSize();
	if (bordersize)
		m_Image->Clear(GetBorderColour());
	
	if (GetBackImage())
	{
		for (uint32 i = bordersize; i < GetSize().X - bordersize; i++)
			for (uint32 j = bordersize; j < GetSize().Y - bordersize; j++)
				if(i - bordersize < GetBackImage()->GetSize().X && j - bordersize < GetBackImage()->GetSize().Y)
					m_Image->SetPixel(i, j, GetBackImage()->GetPixel(Vector2(float32(i - bordersize), float32(j - bordersize))));
				else
					m_Image->SetPixel(i, j, GetBackColour());
	}
	else
	{
		const Vector2 origin((float32)bordersize);

		if (m_Clicked && m_MouseClickColour != GetBackColour())
			m_Image->DrawRectangle(origin, GetSize() - origin, m_MouseClickColour);
		else if (m_Over)
			m_Image->DrawRectangle(origin, GetSize() - origin, m_MouseOverColour);
		else
			m_Image->DrawRectangle(origin, GetSize() - origin, GetBackColour());
	}

	Vector2 stringDimensions = Helper::CalculateStringDimensions(m_Text, GetFont());

	Helper::RenderText(m_Text, GetFont(), GetForeColour(), m_Image, Vector2(((m_Image->GetSize().X - bordersize + 2) / 2) - (stringDimensions.X / 2), ((m_Image->GetSize().Y - bordersize + 2) / 2) - (stringDimensions.Y / 2)));

	if (m_Texture)
		m_Texture->Drop();

	m_Texture = TextureResourcesManager::GetReference().CreateTexture(m_UniqueName, m_Image);
}


bool Button::IsMouseHover(void)
{
	return (m_Input->GetMousePosition().X > GetLocation().X &&
			m_Input->GetMousePosition().X < (GetLocation() + m_Image->GetSize()).X && 
			m_Input->GetMousePosition().Y > GetLocation().Y && 
			m_Input->GetMousePosition().Y < (GetLocation() + m_Image->GetSize()).Y);
}


END_NAMESPACE
