// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ReflectionGenerator.h>
#include <Public\ArgumentsParser.h>

USING_NAMESPACE

int main(uint8 ArgumentsCount, const char **Arguments)
{
	ArgumentsParser args(ArgumentsCount, Arguments, true);

	if (args.GetCount() >= 2)
	{
		ReflectionGenerator rg(args.GetAsString(0), args.GetAsString(1));
		if (rg.Generate())
			return 0;
	}


	
	//ReflectionGenerator rg("D:\\Projects\\Game Engine\\SourceCode\\Engine\\Engine\\Basic\\Public\\AnyDataType.h", "");
	//if (rg.Generate())
	//	return 0;

	return 1;
}
