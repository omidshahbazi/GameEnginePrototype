// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class LauncherRules : BuildRules
{
	public override string TargetName
	{
		get { return "Launcher"; }
	}

	public override LibraryUseTypes LibraryUseType
	{
		get { return LibraryUseTypes.Executable; }
	}

	public override string[] DependencyModulesName
	{
		get { return new string[] { "Common", "Basic", "Core", "Reflection", "D3DRenderer" }; }
	}
}
