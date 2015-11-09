// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef STRINGUTILITY_H
#define STRINGUTILITY_H

#include <Public\Common.h>


BEGIN_NAMESPACE

class COMMON_API StringUtility
{
public:
	static String StandardizePath(const String &Value);

	static void SplitFilename(const String &QualifiedName, String *OutBasename, String *OutPath);

	static void SplitFullFilename(const String &QualifiedName, String *OutBasename, String *OutExtention, String *OutPath);

	static void SplitBaseFilename(const String &FullName, String *OutBasename, String *OutExtention);

	static const bool IsLowerCase(const char Character);
	static const bool IsUpperCase(const char Character);

	//static String ReplaceAll(const String &Source, const String &ReplaceWhat, const String &ReplaceWithWhat);
};


END_NAMESPACE
#endif // STRINGUTILITY_H
