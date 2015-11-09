// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGUISYSTEM_H
#define IGUISYSTEM_H

#include <Public\IPlugin.h>
#include <Public\IFont.h>
#include <Public\ILabel.h>

BEGIN_NAMESPACE

class IGUIScene;

class IGUISystem : public IPlugin
{
public:
	virtual ~IGUISystem(void) {}

	virtual void Initialize(void) = 0;
	
	virtual IFont *LoadFont(const String &Name, uint32 Size = 50) = 0;
	virtual void DestroyFont(IFont *Font) = 0;

	virtual IGUIScene *CreateGUIScene(void) = 0;
	virtual void DestroyGUIScene(IGUIScene *Scene) = 0;
};

END_NAMESPACE
#endif // IGUISYSTEM_H
