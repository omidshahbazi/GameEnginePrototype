// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Sound.h>
#include <Private\SoundSystem.h>
#include <Public\Core.h>
#include <Public\CTime.h>


BEGIN_NAMESPACE


Sound::Sound(FMOD::System *System, FMOD::Sound *Sound, const String &FileName) :
	m_System(System),
	m_Sound(Sound),
	m_Channel(NULL),
	m_FileName(FileName),
	m_DelayTime(0),
	m_StartTime(0),
	m_EndTime(0),
	m_CurrentPosition(0),
	m_Volume(50),
	m_Length(0),
	m_IsLooped(false),
	m_IsPaused(true),
	m_SampleRate(0)
{
	Stop();
}


Sound::~Sound(void)
{
	if (m_Sound)
		m_Sound->release();

	LOG_INFO_DEBUG("ISound [" + m_FileName + "] destoryed successfully")
}


void Sound::Update(void)
{
	if (m_EndTime > 0)
	{
		if (GetCurrentPosition() == 0)
		{
			if (IsLooped())
			{
				Stop();
				Play(m_DelayTime);
			}
		}
	}
}


void Sound::Play(uint32 DelayTime)
{
	if (m_DelayTime != DelayTime)
		m_DelayTime = DelayTime;

	DoClipping();

	if (IsPaused())
		Resume();
	else
		m_System->playSound(FMOD_CHANNEL_FREE, m_Sound, false, &m_Channel);

}


void Sound::Pause(void)
{
	m_IsPaused = true;
	m_Channel->setPaused(m_IsPaused);
}


bool Sound::IsPaused(void)
{
	m_Channel->getPosition(&m_CurrentPosition, FMOD_TIMEUNIT_MS);
	return m_IsPaused;
}


void Sound::Resume(void)
{
	m_IsPaused = false;
	m_Channel->setPaused(m_IsPaused);
}


void Sound::Stop(void)
{
	if (m_Channel)
		m_Channel->stop();

	m_System->playSound(FMOD_CHANNEL_FREE, m_Sound, true, &m_Channel);

	SetVolume(m_Volume);
	SetLoop(m_IsLooped);

	m_Sound->getLength(&m_Length, FMOD_TIMEUNIT_MS);
	m_Sound->getDefaults(&m_SampleRate, 0, 0, 0);

	Pause();
}


void Sound::SetLoop(bool Flag)
{
	m_IsLooped = Flag;

	if (Flag)
		m_Channel->setMode(FMOD_LOOP_NORMAL);
	else
		m_Channel->setMode(FMOD_LOOP_OFF);
}


void Sound::SetVolume(uint32 Value)
{
	m_Volume = Value;
	m_Channel->setVolume((float)m_Volume / 100);
}


uint32 Sound::GetCurrentPosition(void)
{
	m_Channel->getPosition(&m_CurrentPosition, FMOD_TIMEUNIT_MS);

	return m_CurrentPosition;
}


void Sound::SetClip(uint32 StartTime, uint32 EndTime)
{
	m_CurrentPosition = m_StartTime = StartTime;
	m_EndTime = EndTime;
}


void Sound::DoClipping()
{
	if (m_StartTime > 0)
	{
		if (m_CurrentPosition == 0)
			m_CurrentPosition = m_StartTime;

		m_Channel->setPosition(m_CurrentPosition, FMOD_TIMEUNIT_MS);
	}

	uint32 sysHi, sysLo;

	// For accurate sample playback get the current system "tick"
	m_System->getDSPClock(&sysHi, &sysLo);

	if (m_DelayTime > 0)
	{
		// Set start offset to a couple of "mixes" in the future, 2048 samples is far enough in the future to avoid issues with mixer timings
		FMOD_64BIT_ADD(sysHi, sysLo, 0, m_DelayTime * GetSampleRate() / 1000);
		m_Channel->setDelay(FMOD_DELAYTYPE_DSPCLOCK_START, sysHi, sysLo);
	}

	if (m_EndTime == 0)
		return;

	// Set end offset for 50,000 samples from our start time, which means the end sample will be 100,000
	FMOD_64BIT_ADD(sysHi, sysLo, 0, (m_EndTime - m_CurrentPosition) * GetSampleRate() / 1000);
	m_Channel->setDelay(FMOD_DELAYTYPE_DSPCLOCK_END, sysHi, sysLo);
}

END_NAMESPACE
