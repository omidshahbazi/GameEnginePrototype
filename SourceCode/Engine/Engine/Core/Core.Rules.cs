// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class CoreRules : BuildRules
{
    public override string TargetName
    {
        get { return "Core"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.DynamicLibrary; }
    }

	public override string[] DependencyModulesName
    {
		get { return new string[] { "Common", "Basic", "Reflection", "TinyXML", "FreeImage" }; }
    }
}
