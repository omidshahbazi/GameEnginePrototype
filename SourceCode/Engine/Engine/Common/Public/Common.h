// Copyright 2012-2015 ?????????????. All Rights Reserved.
//#include "Log.h"
//#include "Exception.h"
#include <Public\BasicString.h>
#include <Public\Vector.h>
#ifndef COMMON_H
#define COMMON_H

//#define LAUNCH_MODE


#define USE_BREAK_PROCESS_IF
#ifdef USE_BREAK_PROCESS_IF
#define BREAK_PROCESS_IF(Value) if (Value) \
{ \
	_asm int 3 \
}
#else
#define BREAK_PROCESS_IF(Value);
#endif


#define USE_LOG
#ifdef USE_LOG
#define LOG_TEXT(Text);// Log::GetReference().AddText(Text);
#define LOG_INFO(Text);// Log::GetReference().AddInfo(Text);
#define LOG_WARNING(Text);// Log::GetReference().AddWarning(Text);
#define LOG_ERROR(Text); //Log::GetReference().AddError(Text);
#else
#define LOG_TEXT(Text);
#define LOG_INFO(Text);
#define LOG_WARNING(Text);
#define LOG_ERROR(Text);
#endif

#ifdef _DEBUG
#define LOG_INFO_DEBUG(Text) LOG_INFO(Text)
#define LOG_WARNING_DEBUG(Text) LOG_WARNING(Text)
#define LOG_ERROR_DEBUG(Text) LOG_ERROR(Text)
#endif


#define USE_THROW_EXCEPTION
#if defined(_DEBUG) && defined(USE_THROW_EXCEPTION)
#define THROW_EXCEPTION(Reason, Text, Detail, StopProcess);// Exception::GetReference().Throw(Reason, Text, String(Detail) + __FILE__, StopProcess);
#else
#define THROW_EXCEPTION(Reason, Text, Detail, StopProcess);
#endif

#define THROW_EXCEPTION_AND_RESUME(Reason, Text, Detail) THROW_EXCEPTION(Reason, Text, Detail, false);
#define THROW_EXCEPTION_AND_STOP(Reason, Text, Detail) THROW_EXCEPTION(Reason, Text, Detail, true);


#ifdef _DEBUG
#define ASSERTION(Flag, Text) \
{ \
if (!(Flag)) \
{ \
	THROW_EXCEPTION_AND_STOP(ExceptionReasons::AssertionFailed, #Flag, Text) \
} \
}
#define ASSERTION_LOG(Flag, Text) \
{ \
if (!(Flag)) \
{ \
	THROW_EXCEPTION_AND_RESUME(ExceptionReasons::AssertionFailed, #Flag, Text) \
} \
}
#else
#define ASSERTION(Flag, Text) {}
#define ASSERTION_LOG(Flag, Text) {}
#endif



#define FOR_EACH(Variable_Name, Iteratable) \
for (auto Variable_Name = (Iteratable).GetFirst(), __end = (Iteratable).GetEnd(); Variable_Name != __end; Variable_Name++)


#define FOR_EACH_STD(Variable_Name, Array) \
for (auto Variable_Name : Array)


#define FOR_EACH_MAP(Iterator_Name, Map) \
for (auto Iterator_Name = Map.begin(); Iterator_Name != Map.end(); Iterator_Name++)
//#define FOR_EACH_MAP(MapType, Iterator_Name, Map) \
//	for (MapType::iterator Iterator_Name = Map.begin(); Iterator_Name != Map.end(); Iterator_Name++)


#define IS_TYPE_OF(Pointer, Type) \
	dynamic_cast<Type*>(Pointer)


#define ENABLE_FLAG(Mask, Flag) (Mask) |= (Flag)
#define DISABLE_FLAG(Mask, Flag) (Mask) &= ~(Flag)
#define IS_FLAG_ENABLED(Mask, Flag) (Mask) & (Flag)


BEGIN_NAMESPACE

typedef BasicString<char> String;
typedef BasicString<wchar_t> WString;

typedef List<String> StringsList;

END_NAMESPACE

#pragma warning(disable: 4251)
#endif // COMMON_H
