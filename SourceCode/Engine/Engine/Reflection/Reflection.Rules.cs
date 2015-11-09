// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class ReflectionRules : BuildRules
{
    public override string TargetName
    {
		get { return "Reflection"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.DynamicLibrary; }
    }

	public override string[] DependencyModulesName
    {
		get { return new string[] { "Common", "Basic" }; }
    }
}
