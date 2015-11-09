// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ITEXTBOX_H
#define ITEXTBOX_H

#include <Public\IGUIObject.h>

BEGIN_NAMESPACE

class ITextBox : public IGUIObject
{
public:
	virtual ~ITextBox(void) {}
	
	virtual const String &GetText(void) = 0;

	virtual void SetFocus(bool Focus) = 0;
	virtual bool GetFocus(void) = 0;
};

END_NAMESPACE
#endif // ITEXTBOX_H
