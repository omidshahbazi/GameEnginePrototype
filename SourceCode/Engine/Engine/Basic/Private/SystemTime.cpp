// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\SystemTime.h>

BEGIN_NAMESPACE

_SYSTEMTIME SystemTime::m_Time;


int32 SystemTime::GetHours(void)
{
	GetLocalTime(&m_Time);

	return m_Time.wHour;
}


int32 SystemTime::GetMinutes(void)
{
	GetLocalTime(&m_Time);

	return m_Time.wMinute;
}


int32 SystemTime::GetSeconds(void)
{
	GetLocalTime(&m_Time);

	return m_Time.wSecond;
}

END_NAMESPACE
