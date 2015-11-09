// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifdef _DEBUG

#include <Private\Statistics.h>
#include <Public\Core.h>
//#include "Public/GUISystem/IGUISystem.h"
#include <Public\StringConverter.h>

BEGIN_NAMESPACE

DEFINE_SINGLETON(Statistics)


Statistics::Statistics(void)
{
	m_Core = Core::GetPointer();

	//IFont *font = m_Core->GetGUISystem()->LoadFont("tahoma", 14);

	//if (font)
	//{
	//	m_GUIScene = m_Core->GetGUISystem()->CreateGUIScene();

	//	m_Statistics = m_GUIScene->CreateLabel("lStatistics", Vector2(200, 100), font);
	//	m_Statistics->SetLocation(Vector2(10));
	//	m_Statistics->SetForeColour(Colour::WHITE);
	//	m_Statistics->SetBackColour(Colour(50, 50, 50, 100));
	//	m_Statistics->SetOffset(Vector2(10));
	//}
}


Statistics::~Statistics(void)
{
	//m_GUIScene->DestroyObject(m_Statistics);

	//m_Core->GetGUISystem()->DestroyGUIScene(m_GUIScene);
}


void Statistics::Update(void)
{
	//m_Statistics->SetText("FPS : " + StringConverter::ToString(m_Core->GetFPS()));
}


void Statistics::Render(void)
{
	//m_GUIScene->Render();
}

END_NAMESPACE

#endif
