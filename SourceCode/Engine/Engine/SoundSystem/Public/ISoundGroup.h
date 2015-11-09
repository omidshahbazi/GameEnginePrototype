// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ISOUNDGROUP_H
#define ISOUNDGROUP_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class ISound;

//<Description>
//This is sample description
class ISoundGroup
{
public:
	typedef Vector<ISound*> SoundsList;

public:
	virtual ~ISoundGroup(void) {}

	virtual void Update(void) = 0;

	virtual void Play(void) = 0;
	virtual void Pause(void) = 0;
	virtual void Stop(void) = 0;

	virtual void SetVolume(uint32 Value) = 0;

	virtual const String &GetName(void) const = 0;

	virtual ISound *CreateSound(const String &Filename) = 0;
	virtual ISound *CreateStream(const String &Filename) = 0;

	virtual void DestroySound(ISound *Sound) = 0;

};

END_NAMESPACE
#endif // ISOUNDGROUP_H
