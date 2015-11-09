// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BUTTON_H
#define BUTTON_H

#include <Public\Common.h>
#include <Public\GUISystem\IButton.h>
#include <Public\Vector2.h>
#include <Public\GUISystem\IGUIScene.h>
#include <Public\GUISystem\IFont.h>
#include <Public\GUISystem\ITextBox.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Image.h>
#include <Public\Renderer\ITexture.h>
#include <Public\Input\IInputManager.h>


BEGIN_NAMESPACE

class Button: public IButton
{
public:
	Button(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font);
	~Button(void);

	void Update(void);
	void Render(void);

	void SetFont(IFont *Font);
	
	void SetForeColour(const Colour &Colour);
	void SetBackColour(const Colour &Colour);

	void SetCaption(const String &Text);

	void SetMouseOverColour(const Colour &Colour);
	const Colour &GetMouseOverColour(void)
	{
		return m_MouseOverColour;
	}

	void SetMouseClickColour(const Colour &Colour);
	const Colour &GetMouseClickColour(void)
	{
		return m_MouseClickColour;
	}

	void SetFocus(bool Focus);
	bool GetFocus(void)
	{
		return m_Focus;
	}
	
	bool IsClicked(void)
	{
		return m_Clicked;
	}

private:
	void UpdateData(void);

	bool IsMouseHover(void);

private:
	IRenderEngine *m_Renderer;
	IInputManager *m_Input;

	IGUIScene *m_Holder;
	String m_UniqueName;
	String m_Text;
	Image *m_Image;
	ITexture *m_Texture;
	Colour m_MouseOverColour;
	Colour m_MouseClickColour;

	bool m_IsDirty;
	bool m_Focus;
	bool m_Clicked;
	bool m_Over;

	float32 m_Time;
};

END_NAMESPACE
#endif // BUTTON_H
