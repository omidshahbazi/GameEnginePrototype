// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SYSTEMTIME_H
#define SYSTEMTIME_H

#define _X86_

#include <sysinfoapi.h>
#include <Public\Common.h>


BEGIN_NAMESPACE

class BASIC_API SystemTime
{
public:
	static int32 GetHours(void);
	static int32 GetMinutes(void);
	static int32 GetSeconds(void);

private:
	static _SYSTEMTIME m_Time;
};

END_NAMESPACE
#endif // SYSTEMTIME_H
