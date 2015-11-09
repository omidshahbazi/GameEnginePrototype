// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SOUND_H
#define SOUND_H


#include <Public\SoundSystem\ISound.h>
#include "fmod.hpp"

BEGIN_NAMESPACE

class Sound : public ISound
{
public:
	Sound(FMOD::System *System, FMOD::Sound *Sound, const String &FileName);
	virtual ~Sound(void);

	void Update(void);

	void Play(uint32 DelayTime);
	void Play(void)
	{
		Play(m_DelayTime);
	}

	void Pause(void);
	bool IsPaused(void);

	void Resume(void);

	void Stop(void);

	void SetLoop(bool Flag);
	bool IsLooped(void) const
	{
		return m_IsLooped;
	}

	void SetVolume(uint32 Value);
	uint32 GetVolume(void)
	{
		return m_Volume;
	}

	float32 GetSampleRate(void) const
	{
		return m_SampleRate;
	}

	void SetDelayTime(uint32 Value)
	{
		m_DelayTime = Value;
	}

	uint32 GetDelayTime(void) const
	{
		return m_DelayTime;
	}

	uint32 GetLength(void) const
	{
		return m_Length;
	}

	uint32 GetCurrentPosition(void);

	void SetClip(uint32 StartTime, uint32 EndTime);

private:
	void DoClipping();

private:
	FMOD::System* m_System;
	FMOD::Sound* m_Sound;
	FMOD::Channel *m_Channel;
	String m_FileName;

	uint32 m_DelayTime;

	uint32 m_StartTime, m_EndTime;
	uint32 m_CurrentPosition;

	bool m_IsLooped;
	bool m_IsPaused;

	uint32 m_Volume;
	uint32 m_Length;

	float32 m_SampleRate;
};

END_NAMESPACE
#endif // SOUND_H
