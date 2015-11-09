// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ISOUND_H
#define ISOUND_H

#include <Public\Common.h>

BEGIN_NAMESPACE
	
//<Description>
//This is sample description
class ISound
{
public:
	virtual ~ISound(void) {}

	virtual void Update(void) = 0;

	virtual void Play(void) = 0;
	virtual void Play(uint32 DelayTime) = 0;

	virtual void Pause(void) = 0;
	virtual bool IsPaused(void) = 0;
	virtual void Stop(void) = 0;

	virtual void SetLoop(bool Flag) = 0;
	virtual bool IsLooped(void) const = 0;

	virtual void SetVolume(uint32 Value) = 0;
	virtual uint32 GetVolume(void) = 0;

	virtual float32 GetSampleRate(void) const = 0;

	virtual void SetDelayTime(uint32 Value) = 0;
	virtual uint32 GetDelayTime(void) const = 0;

	virtual uint32 GetLength(void) const = 0;

	virtual uint32 GetCurrentPosition(void) = 0;

	virtual void SetClip(uint32 StartTime, uint32 EndTime) = 0;
};

END_NAMESPACE
#endif // ISOUND_H
