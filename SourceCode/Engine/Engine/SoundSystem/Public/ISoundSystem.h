// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ISOUNDSYSTEM_H
#define ISOUNDSYSTEM_H

#include <Public\IPlugin.h>

BEGIN_NAMESPACE

class ISoundGroup;

//<Description>
//This is sample description
class ISoundSystem : public IPlugin
{
public:
	typedef Vector<ISoundGroup*> SoundGroupsList;

public:
	virtual ~ISoundSystem(void) {}

	virtual void Initialize(uint32 maxChannels = 100) = 0;

	virtual void Update(void) = 0;

	virtual ISoundGroup *CreateGroup(const String &Name) = 0;
	virtual ISoundGroup *GetGroup(const String &Name) = 0;
	virtual void DestroyGroup(const String &Name) = 0;
	virtual void DestroyGroup(ISoundGroup *Group) = 0;
};

END_NAMESPACE
#endif // ISOUNDSYSTEM_H
