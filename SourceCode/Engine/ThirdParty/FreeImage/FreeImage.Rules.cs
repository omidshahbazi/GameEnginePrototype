// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class FreeImageRules : BuildRules
{
	public override string TargetName
	{
		get { return "FreeImage"; }
	}

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.ProjectFile; }
    }

	public override string ProjectFilePath
	{
		get { return "Source\\FreeImage.2013.sln"; }
	}
}