// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CTIME_H
#define CTIME_H

//
// CTime.h because we have a conflict with time.h of std 
//



#include <Public\Common.h>
#include <Public\Singleton.h>


BEGIN_NAMESPACE
	
//<Description>
//This is sample description
class BASIC_API CTime
{
	DECLARE_SINGLETON(CTime)

private:
	CTime(void);
	//~CTime(void);

public:
	void Reset(void);
	void Tick(void);

	INLINE float32 GetRealTime(void)
	{
		return m_RealTime;
	}
	
	INLINE float32 GetTime(void)
	{
		return m_Time;
	}
	
	INLINE float32 GetDeltaTime(void)
	{
		return m_DeltaTime;
	}
	
	INLINE float32 GetStartTime(void)
	{
		return m_StartTime;
	}
	
	INLINE float32 GetTimeScale(void)
	{
		return m_TimeScale;
	}

	INLINE void SetTimeScale(float32 Value)
	{
		m_TimeScale = Value;
	}

private:
	float32 m_StartTime;
	float32 m_RealTime;
	float32 m_Time;
	float32 m_TimeScale;
	float32 m_LastTime;
	float32 m_DeltaTime;
};

typedef CTime Time;

END_NAMESPACE
#endif // CTIME_H
