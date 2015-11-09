// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGUISCENE_H
#define IGUISCENE_H

#include <Public\Vector2.h>
#include <Public\IFont.h>
#include <Public\ILabel.h>
#include <Public\ITextBox.h>
#include <Public\IButton.h>
#include <Public\IProgressBar.h>

BEGIN_NAMESPACE

class IGUIScene
{
public:
	typedef Vector<IGUIObject*> GUIObjectList;

public:
	virtual ~IGUIScene(void) {}
	
	virtual ILabel *CreateLabel(const String &Name, const Vector2 &Size, IFont *Font, const String &Text = "") = 0;
	
	virtual ITextBox *CreateTextBox(const String &Name, const Vector2 &Size, IFont *Font) = 0;

	virtual IButton *CreateButton(const String &Name, const Vector2 &Size, IFont *Font) = 0;

	virtual IProgressBar *CreateProgressBar(const String &Name, const Vector2 &Size, IFont *Font) = 0;

	virtual void DestroyObject(IGUIObject *Object) = 0;

	virtual void Render(void) = 0;

	virtual void Update(void) = 0;

};

END_NAMESPACE
#endif // IGUISCENE_H
