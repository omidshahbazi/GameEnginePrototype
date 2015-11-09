// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\FunctionType.h>

BEGIN_NAMESPACE

AnyDataType FunctionType::Invoke(void *TargetObject) const
{
	AnyDataType returnValue;
	InvokeInternal(TargetObject, returnValue, NULL);
	return returnValue;
}


AnyDataType FunctionType::Invoke(void *TargetObject, const AnyDataType &Argument) const
{
	ArgumentsList args;
	args.Add(Argument);

	AnyDataType returnValue;
	InvokeInternal(TargetObject, returnValue, &args);
	return returnValue;
}


AnyDataType FunctionType::Invoke(void *TargetObject, const ArgumentsList &Arguments) const
{
	AnyDataType returnValue;
	InvokeInternal(TargetObject, returnValue, &Arguments);
	return returnValue;
}


END_NAMESPACE
