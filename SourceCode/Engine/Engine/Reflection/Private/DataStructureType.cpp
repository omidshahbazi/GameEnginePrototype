// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\DataStructureType.h>

BEGIN_NAMESPACE


AnyDataType DataStructureType::CreateInstance(void) const
{
	AnyDataType returnValue;
	CreateInstanceInternal(returnValue, NULL);
	return returnValue;
}


AnyDataType DataStructureType::CreateInstance(const AnyDataType &Argument) const
{
	ArgumentsList args;
	args.Add(Argument);

	AnyDataType returnValue;
	CreateInstanceInternal(returnValue, &args);
	return returnValue;
}


AnyDataType DataStructureType::CreateInstance(const ArgumentsList &Arguments) const
{
	AnyDataType returnValue;
	CreateInstanceInternal(returnValue, &Arguments);
	return returnValue;
}


END_NAMESPACE
