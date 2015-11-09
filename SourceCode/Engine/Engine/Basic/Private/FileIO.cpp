// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\FileIO.h>
#include <Public\File.h>
#include <Public\Utility.h>

BEGIN_NAMESPACE


DEFINE_SINGLETON(FileIO)


FileIO::FileIO(void)
{
}


FileIO::~FileIO(void)
{
}


File *FileIO::OpenFile(const String &FilePath)
{
	if (Utility::FileExists(FilePath))
		return new File(FilePath);

	return NULL;
}


File *FileIO::OpenFile(const String &FilePath, bool Append)
{
	return new File(FilePath, Append);
}


String FileIO::ReadText(const String &FilePath)
{
	if (Utility::FileExists(FilePath))
		return File(FilePath).ReadText();

	return "";
}


StringsList FileIO::ReadLines(const String &FilePath)
{
	if (!Utility::FileExists(FilePath))
		return StringsList();

	return File(FilePath).ReadText().Split("\n");
}


void FileIO::WriteText(const String &FilePath, const String &Text)
{
	File f(FilePath, false);

	f.WriteText(Text);
}

END_NAMESPACE
