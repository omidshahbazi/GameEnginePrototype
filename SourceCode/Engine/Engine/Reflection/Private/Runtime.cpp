// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Runtime.h>
#include <Private\RuntimeImplementation.h>

BEGIN_NAMESPACE


void *Runtime::CreateInstance(const String &TypeName)
{
	const DataStructureType const *type = RuntimeImplementation::GetDataStructureType(TypeName);

	ASSERTION(type != NULL, TypeName + " doesn't exists")

		AnyDataType data = type->CreateInstance();

	if (data.GetValueTypes() == ValueTypes::Void)
		return data.GetAsVoid();

	return NULL;
}


void *Runtime::CreateInstance(const String &TypeName, const AnyDataType &Argument)
{
	const DataStructureType const *type = RuntimeImplementation::GetDataStructureType(TypeName);

	ASSERTION(type != NULL, TypeName + " doesn't exists")

		AnyDataType data = type->CreateInstance(Argument);

	if (data.GetValueTypes() == ValueTypes::Void)
		return data.GetAsVoid();

	return NULL;
}


void *Runtime::CreateInstance(const String &TypeName, const ArgumentsList &Arguments)
{
	const DataStructureType const *type = RuntimeImplementation::GetDataStructureType(TypeName);

	ASSERTION(type != NULL, TypeName + " doesn't exists")

		AnyDataType data = type->CreateInstance(Arguments);

	if (data.GetValueTypes() == ValueTypes::Void)
		return data.GetAsVoid();

	return NULL;
}


END_NAMESPACE
