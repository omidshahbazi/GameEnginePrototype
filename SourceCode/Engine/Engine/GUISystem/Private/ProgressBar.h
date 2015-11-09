// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <Public\Common.h>
#include <Public\GUISystem\IProgressBar.h>
#include <Public\Vector2.h>
#include <Public\GUISystem\IGUIScene.h>
#include <Public\GUISystem\IFont.h>
#include <Public\GUISystem\ITextBox.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Image.h>
#include <Public\Renderer\ITexture.h>
#include <Public\Input\IInputManager.h>


BEGIN_NAMESPACE

class ProgressBar: public IProgressBar
{
public:
	ProgressBar(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font);
	~ProgressBar(void);

	void Update(void);
	void Render(void);

	void SetFont(IFont *Font);
	
	void SetForeColour(const Colour &Colour);
	void SetBackColour(const Colour &Colour);

	void SetPrecent(float32 Precent);

	void SetBarColour(const Colour &Colour);
	const Colour &GetBarColour(void)
	{
		return m_BarColour;
	}

	void SetBarImage(Image *Image)
	{
		m_BarImage = Image;
	}
	Image *GetBarImage(void)
	{
		return m_BarImage;
	}

	void SetDisplayText(bool DisplayText);
	bool GetDisplayText(void)
	{
		return m_DisplayText;
	}

private:
	void UpdateData(void);

private:
	IRenderEngine *m_Renderer;
	IInputManager *m_Input;

	IGUIScene *m_Holder;
	String m_UniqueName;
	Image *m_Image;
	Image *m_BarImage;
	ITexture *m_Texture;
	Colour m_BarColour;
	float32 m_Precent;

	bool m_IsDirty;
	bool m_DisplayText;

};

END_NAMESPACE
#endif // PROGRESSBAR_H
