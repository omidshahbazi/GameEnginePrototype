// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\CTime.h>
#include <Windows.h>


BEGIN_NAMESPACE

DEFINE_SINGLETON(CTime)


CTime::CTime(void) :
m_StartTime(0),
m_RealTime(0),
m_Time(0),
m_TimeScale(1.f),
m_LastTime(0),
m_DeltaTime(0)
{
	Reset();
}


//CTime::~CTime(void)
//{
//}


void CTime::Reset(void)
{
	m_LastTime = m_StartTime = timeGetTime() / 1000.0F;
	m_Time = 0.0F;
}


void CTime::Tick(void)
{
	m_LastTime = m_RealTime;
	m_RealTime = (timeGetTime() / 1000.0F) - m_StartTime;
	m_DeltaTime = (m_RealTime - m_LastTime) * m_TimeScale;
	m_Time += m_DeltaTime;
}


END_NAMESPACE
