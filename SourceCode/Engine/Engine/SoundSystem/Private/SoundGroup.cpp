// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\SoundGroup.h>
#include <Public\SoundSystem\ISoundSystem.h>
#include <Private\SoundSystem.h>
#include <Private\Sound.h>
#include <Public\CTime.h>


USING_NAMESPACE


SoundGroup::SoundGroup(ISoundSystem *System, const String &Name) :
	m_System(System), m_Name(Name)
{

}


SoundGroup::~SoundGroup(void)
{
	FOR_EACH(sound, m_SoundsList)
		delete &sound;
	
	LOG_INFO_DEBUG("ISoundGroup destoryed successfully")
}


void SoundGroup::Update(void)
{
	FOR_EACH(sound, m_SoundsList)
		sound->Update();
}


void SoundGroup::Play(void)
{
	FOR_EACH(sound, m_SoundsList)
		sound->Play();
}


void SoundGroup::Pause(void)
{
	FOR_EACH(sound, m_SoundsList)
		sound->Pause();
}


void SoundGroup::Stop(void)
{
	FOR_EACH(sound, m_SoundsList)
		sound->Stop();
}


void SoundGroup::SetVolume(uint32 Value)
{
	FOR_EACH(sound, m_SoundsList)
		sound->SetVolume(Value);
}


ISound *SoundGroup::CreateSound(const String &Filename)
{
	ISound *sound = ((SoundSystem*)m_System)->CreateSound(Filename);

	if (sound)
		m_SoundsList.Add(sound);

	return sound;
}


ISound *SoundGroup::CreateStream(const String &Filename)
{
	ISound *sound = ((SoundSystem*)m_System)->CreateStream(Filename);

	if (sound)
		m_SoundsList.Add(sound);

	return sound;
}


void SoundGroup::DestroySound(ISound *Sound)
{
	m_SoundsList.Remove(Sound);

	delete Sound;
}
