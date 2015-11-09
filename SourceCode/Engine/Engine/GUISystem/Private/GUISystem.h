// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GUISYSTEM_H
#define GUISYSTEM_H
#include <Public\Common.h>
#include <Public\IPlugin.h>
#include <Public\GUISystem\IGUISystem.h>
#include <Public\Vector2.h>
#include <Private\FreeTypeInclude.h>
#include <map>

BEGIN_NAMESPACE

class IRenderable;

class GUISystem : public IGUISystem
{
public:
	GUISystem(void);
	virtual ~GUISystem(void);

	void Install(void);
	const String &GetName(void) const
	{
		static String name = "GUI System";
		return name;
	}
	const String &GetVersion(void) const
	{
		static String version = "1.0.0.0";
		return version;
	}

	void Initialize(void);

	IFont *LoadFont(const String &Name, uint32 Size = 50);
	void DestroyFont(IFont *Font);

	IGUIScene *CreateGUIScene(void);
	void DestroyGUIScene(IGUIScene *Scene);

	//FT_Library GetFTLibrary(void)
	//{
	//	return m_FTLibrary;
	//}

private:
	typedef Vector<IFont*> FontsList;
	typedef Vector<IGUIScene*> GUIScenesList;

	FT_Library m_FTLibrary;

	FontsList m_Fonts;

	GUIScenesList m_GUIScenesList;
};

END_NAMESPACE
#endif // GUISYSTEM_H
