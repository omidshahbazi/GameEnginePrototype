// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\File.h>

BEGIN_NAMESPACE


File::File(const String &FilePath) :
	m_FilePath(FilePath),
	m_File(NULL),
	m_FileSize(0),
	m_WriteMode(false)
{
	OpenFile();
}


File::File(const String &FilePath, bool Append) :
	m_FilePath(FilePath),
	m_File(NULL),
	m_FileSize(0),
	m_WriteMode(true)
{
	OpenFile(Append);
}


File::~File(void)
{
	Close();
}


const String &File::ReadText(void)
{
	m_Buffer.Clear();

	if (!IsOpen())
		return m_Buffer;

	char *buffer = new char[m_FileSize];

	fread(buffer, 1, m_FileSize, m_File);

	buffer[m_FileSize] = '\0';

	m_Buffer = String(buffer, m_FileSize);
	
	return m_Buffer;
}


void File::WriteText(const String &Text)
{
	if (!IsOpen())
		return;

	fwrite(Text.GetBuffer(), 1, Text.GetLength(), m_File);
	fflush(m_File);
}


void File::OpenFile(bool Append)
{
	if (m_FilePath.GetLength() == 0)
	{
		m_File = NULL;
		return;
	}

	if (m_WriteMode)
	{
		//m_File = _wfopen(m_FileName.GetBuffer(), Append ? L"ab" : L"wb");
		fopen_s(&m_File, m_FilePath.GetBuffer(), Append ? "ab" : "wb");
	}
	else
	{
		//m_File = _wfopen(Filename.GetBuffer(), L"rb");
		fopen_s(&m_File, m_FilePath.GetBuffer(), "rb");
	}

	if (m_File)
	{
		fseek(m_File, 0, SEEK_END);
		m_FileSize = ftell(m_File);
		fseek(m_File, 0, SEEK_SET);
	}
}


bool File::IsOpen() const
{
	return (m_File != 0);
}


void File::Close(void)
{
	if (m_File)
	{
		fclose(m_File);
	}
}


File &File::operator <<(const String &Text)
{
	WriteText(Text);

	return *this;
}


bool File::Seek(const int64 &FinalPos, bool RelativeMovement)
{
	if (!IsOpen())
		return false;

	return (fseek(m_File, FinalPos, (RelativeMovement ? SEEK_CUR : SEEK_SET)) == 0);
}


int64 File::GetPosition() const
{
	return ftell(m_File);
}

END_NAMESPACE
