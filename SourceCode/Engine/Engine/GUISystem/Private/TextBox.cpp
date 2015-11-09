// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\TextBox.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Renderer\TextureResourcesManager.h>
#include <Public\Core.h>
#include <Public\Colour.h>
#include <Private\GUIScene.h>
#include <Private\Font.h>
#include <Private\Helper.h>
#include <Public\StringConverter.h>
#include <Public\CTime.h>

BEGIN_NAMESPACE

TextBox::TextBox(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font) :
m_Renderer(Core::GetReference().GetRenderer()),
m_Input(Core::GetReference().GetInputManager()),
m_Holder(Holder),
m_UniqueName(((GUIScene*)m_Holder)->GetUniqeName()),
m_Texture(NULL),
m_CaretImage(NULL),
m_CaretTex(NULL),
m_CaretPosition(0),
m_CaretColour(Colour::BLACK),
m_CaretUpdateCount(Time::GetReference().GetRealTime()),
m_IsDirty(false),
m_Focus(false),
m_BackSpaceCount(Time::GetReference().GetRealTime()),
m_DeleteCount(Time::GetReference().GetRealTime()),
m_RightKeyCount(Time::GetReference().GetRealTime()),
m_LeftKeyCount(Time::GetReference().GetRealTime())
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


TextBox::~TextBox(void)
{
}

void TextBox::Update(void)
{
	if (m_Input->IsMouseClicked(IInputManager::M_LEFT))
	{
		if (m_Input->GetMousePosition().X > GetLocation().X &&
			m_Input->GetMousePosition().X < (GetLocation() + m_Image->GetSize()).X &&
			m_Input->GetMousePosition().Y > GetLocation().Y &&
			m_Input->GetMousePosition().Y < (GetLocation() + m_Image->GetSize()).Y)
			m_Focus = true;
		else
			m_Focus = false;
	}

	if (m_Focus)
	{
		if (m_Input->IsKeyPressed(K_BACK) && m_Text.GetLength() && m_CaretPosition > 0)
		{
			m_Text.Erase(m_CaretPosition - 1, 1);
			m_CaretPosition--;
			m_IsDirty = true;
		}

		if (m_Input->IsKeyDown(K_BACK) && m_Text.GetLength() && Time::GetReference().GetRealTime() - m_BackSpaceCount > 500 && m_CaretPosition > 0)
		{
			m_Text.Erase(m_CaretPosition - 1, 1);
			m_CaretPosition--;
			m_IsDirty = true;
		}

		if (!m_Input->IsKeyDown(K_BACK))
			m_BackSpaceCount = Time::GetReference().GetRealTime();



		if (m_Input->IsKeyPressed(K_DELETE) && m_Text.GetLength() && m_CaretPosition > 0 && m_CaretPosition < m_Text.GetLength())
		{
			m_Text.Erase(m_CaretPosition, 1);
			m_IsDirty = true;
		}

		if (m_Input->IsKeyDown(K_DELETE) && m_Text.GetLength() && Time::GetReference().GetRealTime() - m_DeleteCount > 500 && m_CaretPosition > 0 && m_CaretPosition < m_Text.GetLength())
		{
			m_Text.Erase(m_CaretPosition, 1);
			m_IsDirty = true;
		}

		if (!m_Input->IsKeyDown(K_DELETE))
			m_DeleteCount = Time::GetReference().GetRealTime();



		if (m_Input->IsKeyPressed(K_RIGHT) && m_Text.GetLength())
		{
			if (m_CaretPosition < m_Text.GetLength())
				m_CaretPosition++;
			m_IsDirty = true;
		}

		if (m_Input->IsKeyDown(K_RIGHT) && m_Text.GetLength() && Time::GetReference().GetRealTime() - m_RightKeyCount > 750 && m_CaretPosition < m_Text.GetLength())
		{
			m_CaretPosition++;
			m_IsDirty = true;
		}

		if (!m_Input->IsKeyDown(K_RIGHT))
			m_RightKeyCount = Time::GetReference().GetRealTime();



		if (m_Input->IsKeyPressed(K_LEFT) && m_Text.GetLength() && m_CaretPosition)
		{
			m_CaretPosition--;
			m_IsDirty = true;
		}

		if (m_Input->IsKeyDown(K_LEFT) && m_Text.GetLength() && Time::GetReference().GetRealTime() - m_LeftKeyCount > 750 && m_CaretPosition)
		{
			m_CaretPosition--;
			m_IsDirty = true;
		}

		if (!m_Input->IsKeyDown(K_LEFT))
			m_LeftKeyCount = Time::GetReference().GetRealTime();



		char c = m_Input->GetChar();

		if (c > 0 && c < 256 && c != '\b')
		{
			m_IsDirty = true;
			m_Text = m_Text.SubString(0, m_CaretPosition) + c + m_Text.SubString(m_CaretPosition, m_Text.GetLength() - m_CaretPosition);
			m_CaretPosition++;
		}
	}

	if (m_IsDirty)
	{
		m_IsDirty = false;

		UpdateData();
	}
}

void TextBox::Render(void)
{
	m_Renderer->Draw2DTexture(m_Texture, GetLocation(), true);

	uint32 borderSize = GetBorderSize();
	if (m_Focus)
	{
		if (Time::GetReference().GetRealTime() - m_CaretUpdateCount > 250)
		{
			m_CaretUpdateCount = Time::GetReference().GetRealTime();

			m_DrawCaret = !m_DrawCaret;
		}

		if (m_DrawCaret)
		{
			m_CaretPosOffset = Helper::CalculateStringDimensions(m_Text.SubString(0, m_CaretPosition), GetFont());
			m_CaretPosOffset.Y = float32(borderSize + 5);
			m_CaretPosOffset.X += 5.F;

			if (m_CaretPosOffset.X >= m_Image->GetSize().X - (borderSize + 5))
				m_CaretPosOffset.X = m_Image->GetSize().X - (borderSize + 5);

			m_Renderer->Draw2DTexture(m_CaretTex, GetLocation() + m_CaretPosOffset, true);
		}
	}
}


void TextBox::SetFont(IFont *Font)
{
	if (Font && GetFont() == Font)
		return;

	ITextBox::SetFont(Font);

	m_IsDirty = true;
}


void TextBox::SetForeColour(const Colour &Colour)
{
	if (Colour == GetForeColour())
		return;

	ITextBox::SetForeColour(Colour);

	m_IsDirty = true;
}


void TextBox::SetBackColour(const Colour &Colour)
{
	if (Colour == GetBackColour())
		return;

	ITextBox::SetBackColour(Colour);

	m_IsDirty = true;
}


void TextBox::SetBorderSize(uint32 Size)
{
	if (GetBorderSize() == Size)
		return;

	IGUIObject::SetBorderSize(Size);
	m_IsDirty = true;

	//if (m_CaretImage)
	//	m_Renderer->DestroyImage(m_CaretImage);

	//m_CaretImage = m_Renderer->CreateImage(m_UniqueName + "_Caret", Vector2(1, GetSize().Y - (GetBorderSize() * 2) - 10));

	for (uint32 i = 0; i < m_CaretImage->GetSize().Y; i++)
		m_CaretImage->SetPixel(0, i, Colour::BLACK);

	if (m_CaretTex)
		m_CaretTex->Drop();

	m_CaretTex = TextureResourcesManager::GetReference().CreateTexture(m_UniqueName + "_Caret", m_CaretImage);
}


void TextBox::SetFocus(bool Focus)
{
	m_Focus = Focus;
}


void TextBox::UpdateData(void)
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
		if (i - borderSize < GetBackImage()->GetSize().X && j - borderSize < GetBackImage()->GetSize().Y)
			m_Image->SetPixel(i, j, GetBackImage()->GetPixel(Vector2(float32(i - borderSize), float32(j - borderSize))));
		else
			m_Image->SetPixel(i, j, GetBackColour());
	}
	else
	{
		m_Image->DrawRectangle(origin, GetSize() - origin, GetBackColour());
	}

	if (m_CaretPosOffset.X >= m_Image->GetSize().X - (borderSize + 5))
		Helper::RenderText(m_Text, GetFont(), GetForeColour(), m_Image, Vector2(float32(borderSize + 2), float32(borderSize + 4)), true);
	else
		Helper::RenderText(m_Text, GetFont(), GetForeColour(), m_Image, Vector2(float32(borderSize + 2), float32(borderSize + 4)));

	if (m_Texture)
		m_Texture->Drop();

	m_Texture = TextureResourcesManager::GetReference().CreateTexture(m_UniqueName, m_Image);

}


END_NAMESPACE
