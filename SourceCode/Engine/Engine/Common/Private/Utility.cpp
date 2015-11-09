// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Utility.h>
#include <Public\StringUtility.h>
#include <fstream>
#include <Windows.h>
#include <direct.h>

BEGIN_NAMESPACE


bool Utility::FileExists(const String &FilePath)
{
	std::ifstream file(FilePath.GetBuffer());

	return file.is_open();
}


bool Utility::DirectoryExists(const String &DirectoryPath)
{
	DWORD attr = GetFileAttributesA(DirectoryPath.GetBuffer());

	if (attr != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_DIRECTORY)
		return true;

	return false;
}


void Utility::MakeDirectory(const String &DirectoryPath)
{
	StringsList folders;

	String path = DirectoryPath.Replace("\\", "/");
	if (path.EndsWith("/"))
		path.Erase(path.GetLength() - 1);

	int32 index;

	while (!DirectoryExists(path))
	{
		index = path.FindLast('/');

		if (index > 0)
		{
			folders.Add(path.SubString(index));

			path.Erase(index);
		}
	}

	for (int32 i = folders.GetSize() - 1; i >= 0; i--)
	{
		path += folders[i];

		_mkdir(path.GetBuffer());
	}
}


void Utility::GetFiles(StringsList &Files, const String &Directory, bool Recursive, const String &Extensions)
{
	WIN32_FIND_DATA data;

	String searchDir = Directory + "\\*.*",
		directory = Directory + (Directory.EndsWith("\\") || Directory.EndsWith("/") ? "" : "/");

	HANDLE res = FindFirstFile(searchDir.GetBuffer(), &data);

	if (res == INVALID_HANDLE_VALUE)
		return;
	else
	{
		String fileName, extension;

		do
		{
			if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				fileName = data.cFileName;

				if (Extensions.GetLength())
				{
					StringUtility::SplitBaseFilename(fileName, NULL, &extension);

					if (Extensions.Find("." + extension) != -1)
						Files.Add(directory + fileName);
				}
			}

		} while (FindNextFile(res, &data) != 0);

		FindClose(res);

		if (Recursive)
		{
			StringsList temp = Utility::GetDirectories(Directory);

			FOR_EACH(dir, temp)
				GetFiles(Files, directory + *dir, Recursive, Extensions);
		}
	}
}


StringsList Utility::GetDirectories(const String &Directory)
{
	StringsList list;

	WIN32_FIND_DATA data;

	String dir = Directory + "\\*.*";

	HANDLE res = FindFirstFile(dir.GetBuffer(), &data);

	if (res == INVALID_HANDLE_VALUE)
		return list;
	else
	{
		do
		{
			if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				if (String(data.cFileName).FindFirst('.') > -1 || String(data.cFileName).Find("..") > -1)
					continue;

				list.Add(String(data.cFileName) + "\\");
			}

		} while (FindNextFile(res, &data) != 0);

		FindClose(res);
	}

	return list;
}


uint32 Utility::Random(uint32 Minimum, uint32 Maximum)
{
	srand(clock());
	return std::rand() % (Maximum - Minimum + 1) + Minimum;
}


END_NAMESPACE
