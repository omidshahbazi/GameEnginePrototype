// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef EXCEPTION_H
#define EXCEPTION_H
#ifdef _DEBUG


#include <Public\Common.h>
#include <Public\Singleton.h>
#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

REFLECTION_ENUM()
enum class ExceptionReasons
{
	Unknown = 0,
	AssertionFailed,
	FileNotFound,
	InvalidParameter,
	PerformanceHit,
	InvalidOperation
};

class CORE_API Exception
{
	DECLARE_SINGLETON(Exception)

private:
	Exception(void) {}

public:
	void Throw(const ExceptionReasons &Reason, const String &Text, const String &Detail, bool StopProcess = false);
};

END_NAMESPACE

#endif
#endif // EXCEPTION_H
