// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FILE_H
#define FILE_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class BASIC_API File
{
public:
	// Use this for reading a file
	File(const String &FilePath);
	// Use this for writing a file
	File(const String &FilePath, bool Append);
	~File(void);

	const String &ReadText(void);
	
	void WriteText(const String &Text);

	bool IsOpen(void) const;

	void Close(void);
	
	File &operator <<(const String &Text);

	const String &GetFilePath(void) const
	{
		return m_FilePath;
	}

	const int64 &GetSize(void) const
	{
		return m_FileSize;
	}

	bool IsWriteMode(void) const
	{
		return m_WriteMode;
	}

	bool Seek(const int64 &FinalPos, bool RelativeMovement = false);

	int64 GetPosition(void) const;

private:
	void OpenFile(bool Append = false);

private:
	String m_FilePath;
	FILE *m_File;
	String m_Buffer;
	int64 m_FileSize;
	bool m_WriteMode;
};

END_NAMESPACE
#endif // FILE_H
