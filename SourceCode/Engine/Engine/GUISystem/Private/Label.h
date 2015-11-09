// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LABEL_H
#define LABEL_H

#include <Public\GUISystem\ILabel.h>
#include <Public\GUISystem\IGUIScene.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\Image.h>
#include <Public\Renderer\ITexture.h>
#include <Private\FreeTypeInclude.h>

BEGIN_NAMESPACE

class IGUISystem;

class Label : public ILabel
{
public:
	Label(IGUIScene *Holder, const String &Name, const Vector2 &Size, IFont *Font, const String &Text);
	~Label(void);
	
	void Update(void) {}
	void Render(void);

	void SetFont(IFont *Font);

	void SetForeColour(const Colour &Colour);
	void SetBackColour(const Colour &Colour);
	
	void SetOffset(const Vector2 &Offset);
	const Vector2 &GetOffset(void)
	{
		return m_Offset;
	}

	void SetText(const String &Text);
	const String &GetText(void)
	{
		return m_Text;
	}
	
private:
	void UpdateData(void);

private:
	IRenderEngine *m_Renderer;

	IGUIScene *m_Holder;
	String m_UniqueName;
	Vector2 m_Offset;
	String m_Text;
	Image *m_Image;
	ITexture *m_Texture;

	bool m_IsDirty;
};

END_NAMESPACE
#endif // LABEL_H
