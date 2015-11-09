// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IBUTTON_H
#define IBUTTON_H

#include <Public\IGUIObject.h>

BEGIN_NAMESPACE

class IButton : public IGUIObject
{
public:
	virtual ~IButton(void) {}
	
	virtual void SetCaption(const String &Text) = 0;

	virtual void SetMouseOverColour(const Colour &Colour) = 0;
	virtual const Colour &GetMouseOverColour(void) = 0;

	virtual void SetMouseClickColour(const Colour &Colour) = 0;
	virtual const Colour &GetMouseClickColour(void) = 0;

	virtual void SetFocus(bool Focus) = 0;
	virtual bool GetFocus(void) = 0;

	virtual bool IsClicked(void) = 0;
};

END_NAMESPACE
#endif // IBUTTON_H
