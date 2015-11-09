// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGUIOBJECT_H
#define IGUIOBJECT_H

#include <Public\Vector2.h>
#include <Public\IFont.h>
#include <Public\Colour.h>
#include <Public\Image.h>

BEGIN_NAMESPACE

class IGUIObject
{
public:
	IGUIObject(void) :
		m_Visible(true),
		m_Font(NULL),
		m_Image(NULL),
		m_Bordersize(0)
	{
	}

	virtual ~IGUIObject(void) {}

	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
	
protected:
	virtual void SetSize(const Vector2 &Size)
	{
		m_Size = Size;
	}
	void SetName(const String &Name)
	{
		m_Name = Name;
	}

public:
	virtual const String &GetName(void) const
	{
		return m_Name;
	}

	virtual const Vector2 &GetSize(void)
	{
		return m_Size;
	}
		
	virtual void SetLocation(const Vector2 &Location)
	{
		m_Location = Location;
	}
	virtual const Vector2 &GetLocation(void)
	{
		return m_Location;
	}

	virtual void SetVisible(bool Visible)
	{
		m_Visible = Visible;
	}
	virtual  bool GetVisible(void)
	{
		return m_Visible;
	}

	virtual void SetFont(IFont *Font)
	{
		m_Font = Font;
	}
	virtual IFont *GetFont(void)
	{
		return m_Font;
	}

	virtual void SetForeColour(const Colour &Colour)
	{
		m_ForeColour = Colour;
	}
	virtual const Colour &GetForeColour(void)
	{
		return m_ForeColour;
	}

	virtual void SetBackColour(const Colour &Colour)
	{
		m_BackColour = Colour;
	}
	virtual const Colour &GetBackColour(void)
	{
		return m_BackColour;
	}

	virtual void SetBackImage(Image *Image)
	{
		m_Image = Image;
	}
	virtual Image *GetBackImage(void)
	{
		return m_Image;
	}

	virtual void SetBorderSize(int32 Size)
	{
		m_Bordersize = Size;
	}
	virtual int32 GetBorderSize(void)
	{
		return m_Bordersize;
	}

	virtual void SetBorderColour(const Colour &Colour)
	{
		m_BorderColour = Colour;
	}
	virtual const Colour &GetBorderColour(void)
	{
		return m_BorderColour;
	}

private:
	String m_Name;
	Vector2 m_Size;
	Vector2 m_Location;
	bool m_Visible;
	IFont *m_Font;
	Colour m_ForeColour;
	Colour m_BackColour;
	Image *m_Image;

	uint32 m_Bordersize;
	Colour m_BorderColour;
};

END_NAMESPACE
#endif // IGUIOBJECT_H
