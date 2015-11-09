// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class CommonRules : BuildRules
{
    public override string TargetName
    {
        get { return "Common"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.DynamicLibrary; }
    }
}
