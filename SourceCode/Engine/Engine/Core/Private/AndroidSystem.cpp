// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\AndroidSystem.h>

#include <Public\Utility.h>
#include <Public\StringUtility.h>
#include <Public\Core.h>

BEGIN_NAMESPACE

DEFINE_SINGLETON(AndroidSystem)

AndroidSystem::AndroidSystem(void)
{
}


AndroidSystem::~AndroidSystem(void)
{
}


//void AddDirectoryToZip(ZipFile &Zip, const String &Directory, const String &Root)
//{
//	StringsList list = Utility::GetDirectories(Directory);
//
//	FOR_EACH(dir, list)
//		AddDirectoryToZip(Zip, Directory + *dir, Root);
//
//	Utility::GetFiles(list, Directory);
//
//	FOR_EACH(file, list)
//		Zip.AddFile(*file, (*file).Remove(Root));
//}


void AndroidSystem::Export(void)
{
	//ZipFile zf("d:/launcher.apk", ZipFile::M_ZIP);
	
	//const String &androidPath = Core::GetReference().GetAndroidPath();
	//AddDirectoryToZip(zf, androidPath, androidPath);
}

END_NAMESPACE
