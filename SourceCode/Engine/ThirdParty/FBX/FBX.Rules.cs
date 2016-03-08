// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class FBXRules : BuildRules
{
    public override string TargetName
    {
        get { return "FBX"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.UseOnly; }
    }

	public override string[] OutputsFilePath
	{
		get { return new string[] { "Binaries\\x86\\debug\\libfbxsdk-md.lib" }; }
	}
}