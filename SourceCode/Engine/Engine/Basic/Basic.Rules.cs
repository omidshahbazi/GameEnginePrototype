// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class BasicRules : BuildRules
{
	public override string TargetName
	{
		get { return "Basic"; }
	}

	public override LibraryUseTypes LibraryUseType
	{
		get { return LibraryUseTypes.DynamicLibrary; }
	}

	public override string[] DependencyModulesName
	{
		get { return new string[] { "Common" }; }
	}

	public override string[] IncludeModulesName
	{
		get { return new string[] { "Reflection" }; }
	}

	public override string[] AdditionalCompileFile
	{
		get
		{
			return new string[] {
			"Common\\Private\\BasicString.cpp",
			
			"Reflection\\Private\\Type.cpp",
			"Reflection\\Private\\EnumType.cpp",
			"Reflection\\Private\\ImplementEnumType.cpp",
			"Reflection\\Private\\RuntimeImplementation.cpp"};
		}
	}

	public override string[] DependencyStaticLibraries
	{
		get { return new string[] { "winmm.lib" }; }
	}
}
