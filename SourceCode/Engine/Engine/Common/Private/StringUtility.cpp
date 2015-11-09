// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\StringUtility.h>

using namespace std;


BEGIN_NAMESPACE


String StringUtility::StandardizePath(const String &Value)
{
	String path = Value;

	path.Replace('\\', '/');

	if (path[path.GetLength() - 1] != '/')
		path += "/";

	//std::replace(path.begin(), path.end(), '/', '\\');

	//if(path[path.GetLength() - 1] != '\\' )
	//	path += '\\';

	return path;
}


void StringUtility::SplitFilename(const String &QualifiedName, String *OutBasename, String *OutPath)
{
	String path = QualifiedName;
	// Replace \ with / first
	path.Replace('\\', '/');
	// split based on final /
	int32 i = path.FindLast('/');

	if (i == -1)
	{
		if (OutBasename)
			*OutBasename = QualifiedName;

		if (OutPath)
			OutPath->Clear();
	}
	else
	{
		if (OutBasename)
			*OutBasename = path.SubString(i + 1);

		if (OutPath)
			*OutPath = path.SubString(0, i + 1);
	}
}


void StringUtility::SplitFullFilename(const String &QualifiedName, String *OutBasename, String *OutExtention, String *OutPath)
{
	String fullName;
	SplitFilename(QualifiedName, &fullName, OutPath);
	SplitBaseFilename(fullName, OutBasename, OutExtention);
}


void StringUtility::SplitBaseFilename(const String &FullName, String *OutBasename, String *OutExtention)
{
	int32 i = FullName.FindLast('.');

	if (i == -1)
	{
		if (OutBasename)
			*OutBasename = FullName;

		if (OutExtention)
			OutExtention->Clear();
	}
	else
	{
		if (OutBasename)
			*OutBasename = FullName.SubString(0, i);

		if (OutExtention)
			*OutExtention = FullName.SubString(i + 1);
	}
}


const bool StringUtility::IsLowerCase(const char Character)
{
	return (Character >= 'a' && Character <= 'z');
}


const bool StringUtility::IsUpperCase(const char Character)
{
	return (Character >= 'A' && Character <= 'Z');
}


//String StringUtility::ReplaceAll(const String &Source, const String &ReplaceWhat, const String &ReplaceWithWhat)
//{
//	String result = Source;
//
//	int32 pos = 0;
//
//	while (true)
//	{
//		pos = result.Find(ReplaceWhat, pos);
//
//		if (pos == -1)
//			break;
//
//		result.Replace(ReplaceWhat, ReplaceWithWhat);
//		pos += ReplaceWithWhat.GetLength();
//	}
//
//	return result;
//}

END_NAMESPACE
