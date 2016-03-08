// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class TinyXMLRules : BuildRules
{
    public override string TargetName
    {
        get { return "TinyXML"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.StaticLibrary; }
    }
}