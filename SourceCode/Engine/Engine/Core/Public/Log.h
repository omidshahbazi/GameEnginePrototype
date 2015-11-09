// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LOG_H
#define LOG_H

#include <Public\Common.h>

#ifdef USE_LOG

#include <Public\Singleton.h>
#include <Public\ListenerHolder.h>
#include <Public\ReflectionDefinitions.h>


BEGIN_NAMESPACE

REFLECTION_ENUM()
enum class LogTypes
{
	Info = 0,
	Warning,
	Error
};

class CORE_API Log
{
	DECLARE_SINGLETON(Log)

	BEGIN_DECLARE_LISTENER_HOLDER
		virtual void OnAdd(const String &Text, LogTypes Type) = 0;
	END_DECLARE_LISTENER_HOLDER

private:
	Log(void) {}

public:
	void AddText(const String &Text, LogTypes Type = LogTypes::Info);

	void AddInfo(const String &Text);
	void AddWarning(const String &Text);
	void AddError(const String &Text);

	static const String GetTimePrefix(void);
};

END_NAMESPACE

#endif
#endif // LOG_H
