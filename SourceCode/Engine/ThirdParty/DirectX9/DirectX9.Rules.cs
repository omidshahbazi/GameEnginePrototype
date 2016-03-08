// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class DirectX9Rules : BuildRules
{
	public override string TargetName
	{
		get { return "DirectX9"; }
	}

	public override LibraryUseTypes LibraryUseType
	{
		get { return LibraryUseTypes.UseOnly; }
	}

	public override string[] OutputsFilePath
	{
		get { return new string[] { "Binaries\\x86\\d3d9.lib", "Binaries\\x86\\d3dx9.lib" }; }
	}
}