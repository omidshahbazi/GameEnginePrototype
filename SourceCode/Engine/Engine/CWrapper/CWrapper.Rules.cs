// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class CWrapperRules : BuildRules
{
	public override string TargetName
	{
		get { return "CWrapper"; }
	}

	public override LibraryUseTypes LibraryUseType
	{
		get { return LibraryUseTypes.DynamicLibrary; }
	}

	public override string[] DependencyModulesName
	{
		get { return new string[] { "Common", "Basic", "Core", "Reflection", "D3DRenderer" }; }
	}
}
