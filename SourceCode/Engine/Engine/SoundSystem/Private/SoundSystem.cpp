// Copyright 2012-2015 ?????????????. All Rights Reserved.

#include <Public\Core.h>
#include <Private\SoundSystem.h>
#include <Private\SoundGroup.h>
#include <Private\Sound.h>
#include <Public\CTime.h>


USING_NAMESPACE


SoundSystem::SoundSystem(void) :
	m_System(NULL)
{

}


SoundSystem::~SoundSystem(void)
{
	FOR_EACH(group, m_SoundGroupsList)
		delete &group;

	if (m_System)
		m_System->release();
	
	LOG_INFO_DEBUG("ISoundSystem destoryed successfully")
}


void SoundSystem::Install(void)
{
	Core::GetReference().SetSoundSystem(this);
}


void SoundSystem::Initialize(uint32 maxChannels)
{
	if (FMOD::System_Create(&m_System) != FMOD_OK)
		THROW_EXCEPTION_AND_RESUME(Exception::ER_UNKNOWN, "FMOD Failed to create sound system", "ISoundSystem::Initialize")


	if (m_System->init(maxChannels, FMOD_INIT_NORMAL, 0) != FMOD_OK)
		THROW_EXCEPTION_AND_RESUME(Exception::ER_UNKNOWN, "FMOD Failed to initialize sound system", "ISoundSystem::Initialize")
}


void SoundSystem::Update(void)
{
	FOR_EACH(group, m_SoundGroupsList)
		group->Update();

	m_System->update();
}


ISoundGroup *SoundSystem::CreateGroup(const String &Name)
{
	ISoundGroup *group = GetGroup(Name);

	if (group)
	{
		LOG_WARNING("Sound Group with name [" + Name + "] already exists.")

		return group;
	}

	group = new SoundGroup(this, Name);

	m_SoundGroupsList.Add(group);

	return group;
}


ISoundGroup *SoundSystem::GetGroup(const String &Name)
{
	FOR_EACH(group, m_SoundGroupsList)
		if (group->GetName() == Name)
			return &group;

	return NULL;
}


void SoundSystem::DestroyGroup(const String &Name)
{
	FOR_EACH(group, m_SoundGroupsList)
		if (group->GetName() == Name)
		{
			DestroyGroup(&group);
			return;
		}
}


void SoundSystem::DestroyGroup(ISoundGroup *Group)
{
	m_SoundGroupsList.Remove(Group);

	delete Group;
}


ISound *SoundSystem::CreateSound(const String &Filename)
{
	FMOD_RESULT result;

	FMOD::Sound *fmSound = NULL;

	//result = m_System->createSound((Core::GetReference().GetSoundPath() + Filename).GetBuffer(), (FMOD_HARDWARE | FMOD_2D), 0, &fmSound);

	ISound *sound = NULL;

	if (result != FMOD_OK)
		THROW_EXCEPTION_AND_RESUME(Exception::ER_UNKNOWN, "FMOD Failed to create sound", "SoundSystem::CreateSound")
	else
		sound = new Sound(m_System, fmSound, Filename);

	return sound;
}


ISound *SoundSystem::CreateStream(const String &Filename)
{
	FMOD_RESULT result;

	FMOD::Sound *fmSound = NULL;

	//result = m_System->createStream((Core::GetReference().GetSoundPath() + Filename).GetBuffer(), (FMOD_HARDWARE | FMOD_2D), 0, &fmSound);

	ISound *sound = NULL;

	if (result != FMOD_OK)
		THROW_EXCEPTION_AND_RESUME(Exception::ER_UNKNOWN, "FMOD Failed to create sound", "SoundSystem::CreateSound")
	else
		sound = new Sound(m_System, fmSound, Filename);

	return sound;
}

