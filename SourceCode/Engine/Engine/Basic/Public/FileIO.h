// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FILEIO_H
#define FILEIO_H

#include <Public\Common.h>
#include <Public\Singleton.h>
#include <Public\File.h>

BEGIN_NAMESPACE
	
class BASIC_API FileIO
{
	DECLARE_SINGLETON(FileIO)

private:
	FileIO(void);
	~FileIO(void);

public:
	File *OpenFile(const String &FilePath);
	File *OpenFile(const String &FilePath, bool Append);

	String ReadText(const String &FilePath);
	StringsList ReadLines(const String &FilePath);
	void WriteText(const String &FilePath, const String &Text);
};

END_NAMESPACE
#endif // FILEIO_H
