// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GUISCENE_H
#define GUISCENE_H

#include <Public\GUISystem\IGUIScene.h>
#include <Public\GUISystem\IGUIObject.h>

BEGIN_NAMESPACE

class GUIScene: public IGUIScene
{
public:
	GUIScene(void);
	~GUIScene(void);

	ILabel *CreateLabel(const String &Name, const Vector2 &Size, IFont *Font, const String &Text = "");

	ITextBox *CreateTextBox(const String &Name, const Vector2 &Size, IFont *Font);

	IButton *CreateButton(const String &Name, const Vector2 &Size, IFont *Font);

	IProgressBar *CreateProgressBar(const String &Name, const Vector2 &Size, IFont *Font);

	void DestroyObject(IGUIObject *Object);

	void Render(void);

	void Update(void);

	String GetUniqeName(void);

private:
	typedef Vector<IGUIObject*> ObjectsList;

	ObjectsList m_Objects;

	static uint32 m_ObjectsCounter;
};

END_NAMESPACE
#endif // GUISCENE_H
