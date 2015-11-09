// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <Public\IPlugin.h>
#include "fmod.hpp"
#include <Public\SoundSystem\ISoundSystem.h>

BEGIN_NAMESPACE

class ISound;

class SoundSystem : public ISoundSystem
{
public:
	SoundSystem(void);
	~SoundSystem(void);

	void Install(void);
	const String &GetName(void) const
	{
		static String name = "Fmod Sound System";
		return name;
	}
	const String &GetVersion(void) const
	{
		static String version = "1.0.0.0";
		return version;
	}

	void Initialize(uint32 maxChannels = 100);

	void Update(void);

	ISoundGroup *CreateGroup(const String &Name);
	ISoundGroup *GetGroup(const String &Name);
	void DestroyGroup(const String &Name);
	void DestroyGroup(ISoundGroup *Group);

	ISound *CreateSound(const String &Filename);
	ISound *CreateStream(const String &Filename);

private:
	FMOD::System *m_System;

	SoundGroupsList m_SoundGroupsList;
};
END_NAMESPACE
#endif // SOUNDSYSTEM_H
