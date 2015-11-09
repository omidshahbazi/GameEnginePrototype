// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SOUNDGROUP_H
#define SOUNDGROUP_H

#include <Public\SoundSystem\ISoundGroup.h>

BEGIN_NAMESPACE

class ISoundSystem;

class SoundGroup : public ISoundGroup
{
public:
	SoundGroup(ISoundSystem *System, const String &Name);
	~SoundGroup(void);

	void Update(void);

	void Play(void);
	void Pause(void);
	void Stop(void);

	void SetVolume(uint32 Value);

	const String &GetName(void) const
	{
		return m_Name;
	}

	ISound *CreateSound(const String &Filename);
	ISound *CreateStream(const String &Filename);
	void DestroySound(ISound *Sound);

private:
	ISoundSystem *m_System;

	String m_Name;

	SoundsList m_SoundsList;
};

END_NAMESPACE
#endif // SOUNDGROUP_H
