// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <Public\Common.h>
#include <Public\Vector2.h>
#include <Public\GUISystem\IGUIScene.h>
#include <Public\GUISystem\IFont.h>
#include <Public\GUISystem\ITextBox.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Image.h>
#include <Public\Renderer\ITexture.h>
#include <Public\Input\IInputManager.h>

BEGIN_NAMESPACE

class IGUISystem;

class TextBox: public ITextBox
{
public:
	TextBox(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font);
	~TextBox(void);

	void Update(void);
	void Render(void);

	void SetFont(IFont *Font);

	void SetForeColour(const Colour &Colour);
	void SetBackColour(const Colour &Colour);

	void SetBorderSize(uint32 Size);

	const String &GetText(void)
	{
		return m_Text;
	}

	void SetFocus(bool Focus);
	bool GetFocus(void)
	{
		return m_Focus;
	}

private:
	void UpdateData(void);

private:
	IRenderEngine *m_Renderer;
	IInputManager *m_Input;

	IGUIScene *m_Holder;
	String m_UniqueName;
	String m_Text;
	Image *m_Image;
	ITexture *m_Texture;
	
	Image *m_CaretImage;
	ITexture *m_CaretTex;
	uint32 m_CaretPosition;
	bool m_DrawCaret;
	Colour m_CaretColour;
	float32 m_CaretUpdateCount;
	Vector2 m_CaretPosOffset;

	bool m_IsDirty;
	bool m_Focus;

	float32 m_BackSpaceCount;
	float32 m_DeleteCount;
	float32 m_RightKeyCount;
	float32 m_LeftKeyCount;
};

END_NAMESPACE
#endif // TEXTBOX_H
