// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class JSONCPPRules : BuildRules
{
    public override string TargetName
    {
		get { return "JSONCPP"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.StaticLibrary; }
    }
}