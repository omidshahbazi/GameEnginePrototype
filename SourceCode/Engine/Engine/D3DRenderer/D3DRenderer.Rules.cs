// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class D3DRendererRules : BuildRules
{
    public override string TargetName
    {
		get { return "D3DRenderer"; }
    }

	public override LibraryUseTypes LibraryUseType
    {
		get { return LibraryUseTypes.DynamicLibrary; }
    }

	public override string[] DependencyModulesName
    {
		get { return new string[] { "Common", "Basic", "Core", "Reflection", "JSONCPP", "DirectX9", "FBX" }; }
    }
}
