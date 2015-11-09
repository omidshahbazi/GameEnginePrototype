// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef UTILITY_H
#define UTILITY_H

#include <Public\Common.h>
#include <ctime>

BEGIN_NAMESPACE

class COMMON_API Utility
{
public:
	static bool FileExists(const String &FilePath);
	static bool DirectoryExists(const String &DirectoryPath);

	static void MakeDirectory(const String &DirectoryPath);

	static void GetFiles(StringsList &Files, const String &Directory, bool Recursive = false, const String &Extensions = "");

	static StringsList GetDirectories(const String &Directory);

	static uint32 Random(uint32 Minimum, uint32 Maximum);
};

END_NAMESPACE
#endif // UTILITY_H
