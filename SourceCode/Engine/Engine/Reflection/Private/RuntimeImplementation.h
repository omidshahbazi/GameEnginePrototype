// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\HashMap.h>
#include <Public\DataStructureType.h>
#include <Public\EnumType.h>

BEGIN_NAMESPACE

class REFLECTION_API RuntimeImplementation
{
public:
	static const DataStructureType *const GetDataStructureType(const String &TypeName);
	static const EnumType *const GetEnumType(const String &TypeName);

	static void RegisterTypeInfo(Type *Type);
	static void UnregisterTypeInfo(Type *Type);

private:
	typedef HashMap<String, Type*> TypesMap;

private:
	static TypesMap m_DataStructureTypes;
	static TypesMap m_EnumTypes;
};


END_NAMESPACE
