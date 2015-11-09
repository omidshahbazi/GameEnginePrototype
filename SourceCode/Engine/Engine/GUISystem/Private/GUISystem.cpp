// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GUISystem.h>
#include <Public\Core.h>
#include <Private\Font.h>
#include <Private\GUIScene.h>



GUISystem::GUISystem(void)
{
}


GUISystem::~GUISystem(void)
{
	FOR_EACH(font, m_Fonts)
		delete &font;

	FT_Done_FreeType(m_FTLibrary);

	LOG_INFO_DEBUG("IGUISystem destoryed successfully")
}


void GUISystem::Install(void)
{
	Core::GetReference().SetGUISystem(this);
}


void GUISystem::Initialize(void)
{
	FT_Init_FreeType(&m_FTLibrary);
}


IFont *GUISystem::LoadFont(const String &Name, uint32 Size)
{
	//if (m_Fonts.find(Name) != m_Fonts.end())
	//	return m_Fonts[Name];
	
	FT_Face face;

	//FT_Error error = FT_New_Face(m_FTLibrary, (Core::GetReference().GetFontPath() + Name + ".ttf").GetBuffer(), 0, &face);
	//if (error != FT_Err_Ok)
	//{
	//	LOG_ERROR("There was a problem to loading [" + Name + ".ttf]");

	//	return NULL;
	//}

	Font *font = new Font(Name, Size, face);

	m_Fonts.Add(font);
	
	return font;
}


void GUISystem::DestroyFont(IFont *Font)
{
	m_Fonts.Remove(Font);

	delete Font;
}


IGUIScene *GUISystem::CreateGUIScene(void)
{
	IGUIScene *Scene = new GUIScene();
	m_GUIScenesList.Add(Scene);
	return Scene;
}


void GUISystem::DestroyGUIScene(IGUIScene *Scene)
{
	m_GUIScenesList.Remove(Scene);

	delete Scene;
}
