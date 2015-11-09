// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CONSOLE_H
#define CONSOLE_H
#include <Public\Common.h>

BEGIN_NAMESPACE

class Console
{
public:
	static void LogInfo(const String &Text)
	{
		std::cout << Text << "\n";
	}

	static void LogWarning(const String &Text)
	{
		std::cout << "Warning " << Text << "\n";
	}

	static void LogError(const String &Text)
	{
		std::cout << "Error " << Text << "\n";
	}
};

END_NAMESPACE
#endif // CONSOLE_H
