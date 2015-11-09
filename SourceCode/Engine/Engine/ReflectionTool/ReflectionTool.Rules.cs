// Copyright 2012-2015 ?????????????. All Rights Reserved.
using Frontend;

class ReflectionToolRules : BuildRules
{
	public override string TargetName
	{
		get { return "ReflectionTool"; }
	}

	public override LibraryUseTypes LibraryUseType
	{
		get { return LibraryUseTypes.Executable; }
	}

	public override string[] IncludeModulesName
	{
		get { return new string[] { "Common", "Basic", "Core", "Reflection" }; }
	}

	public override string[] AdditionalCompileFile
	{
		get
		{
			return new string[] {
			"Common\\Private\\AllocationPolicy.cpp",
			"Common\\Private\\BasicString.cpp",
			"Common\\Private\\SmallObjectAllocationPolicy.cpp",
			"Common\\Private\\StringUtility.cpp",
			"Common\\Private\\Utility.cpp",
			
			"Basic\\Private\\ArgumentsParser.cpp",
			"Basic\\Private\\File.cpp",
			"Basic\\Private\\FileIO.cpp",
			"Basic\\Private\\SystemTime.cpp",
			"Basic\\Private\\StringConverter.cpp",
			
			"Core\\Private\\Exception.cpp",
			"Core\\Private\\Log.cpp",
			
			"Reflection\\Private\\Enum.cpp",
			"Reflection\\Private\\Type.cpp",
			"Reflection\\Private\\EnumType.cpp",
			"Reflection\\Private\\RuntimeImplementation.cpp",
			"Reflection\\Private\\ImplementDataStructureType.cpp",
			"Reflection\\Private\\ImplementEnumType.cpp",
			"Reflection\\Private\\ImplementFunctionType.cpp",
			"Reflection\\Private\\ImplementPropertyType.cpp"};
		}
	}

	public override Priorities Priority
	{
		get { return Priorities.PreBuildProcess; }
	}
}
