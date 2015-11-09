// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Log.h>

#ifdef USE_LOG

#include <Public\SystemTime.h>
#include <Public\StringConverter.h>
#include <Public\FileIO.h>
#include <Public\Enum.h>
#include <iostream>

using namespace std;

BEGIN_NAMESPACE


DEFINE_SINGLETON(Log)


void Log::AddText(const String &Text, LogTypes Type)
{
	static const EnumType *const type = Enum::GetType("ExceptionReasons");

	FOR_EACH(listener, m_Listeners)
		listener->OnAdd(Text, Type);

	String prefix = GetTimePrefix();

	cout << prefix << " [" << Enum::ToString(type, (int32)Type) << "] " << Text << endl;
}


void Log::AddInfo(const String &Text)
{
	AddText(Text, LogTypes::Info);
}


void Log::AddWarning(const String &Text)
{
	AddText(Text, LogTypes::Warning);
}


void Log::AddError(const String &Text)
{
	AddText(Text, LogTypes::Error);
}


const String Log::GetTimePrefix(void)
{
	return StringConverter::ToString(SystemTime::GetHours()) + ":" + StringConverter::ToString(SystemTime::GetMinutes()) + ":" + StringConverter::ToString(SystemTime::GetSeconds());
}

END_NAMESPACE

#endif
