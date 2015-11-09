// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GUIScene.h>
#include <Private\Label.h>
#include <Private\TextBox.h>
#include <Private\Button.h>
#include <Private\ProgressBar.h>
#include <Public\StringConverter.h>

BEGIN_NAMESPACE

uint32 GUIScene::m_ObjectsCounter(0);

GUIScene::GUIScene(void)
{
}


GUIScene::~GUIScene(void)
{
	FOR_EACH(object, m_Objects)
		delete &object;
}


ILabel *GUIScene::CreateLabel(const String &Name, const Vector2 &Size, IFont *Font, const String &Text)
{
	Label *label = new Label(this, Name, Size, Font, Text);

	m_Objects.Add(label);

	return label;
}


ITextBox *GUIScene::CreateTextBox(const String &Name, const Vector2 &Size, IFont *Font)
{
	TextBox *textBox = new TextBox(this, Name, Size, Font);

	m_Objects.Add(textBox);

	return textBox;
}


IButton *GUIScene::CreateButton(const String &Name, const Vector2 &Size, IFont *Font)
{
	Button *button = new Button(this, Name, Size, Font);

	m_Objects.Add(button);

	return button;
}



IProgressBar *GUIScene::CreateProgressBar(const String &Name, const Vector2 &Size, IFont *Font)
{
	ProgressBar *progressBar = new ProgressBar(this, Name, Size, Font);

	m_Objects.Add(progressBar);

	return progressBar;
}



void GUIScene::DestroyObject(IGUIObject *Object)
{
	m_Objects.Remove(Object);

	delete Object;
}


String GUIScene::GetUniqeName(void)
{
	return "Object " + StringConverter::ToString(m_ObjectsCounter++);
}


void GUIScene::Render(void)
{
	FOR_EACH(object, m_Objects)
		if (object->GetVisible())
			object->Render();
}


void GUIScene::Update(void)
{
	FOR_EACH(object, m_Objects)
		if (object->GetVisible())
			object->Update();
}

END_NAMESPACE
