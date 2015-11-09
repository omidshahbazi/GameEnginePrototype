// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\RuntimeImplementation.h>

BEGIN_NAMESPACE


RuntimeImplementation::TypesMap RuntimeImplementation::m_DataStructureTypes;
RuntimeImplementation::TypesMap RuntimeImplementation::m_EnumTypes;


const DataStructureType *const RuntimeImplementation::GetDataStructureType(const String &TypeName)
{
	if (m_DataStructureTypes.ContainsKey(TypeName))
		return (DataStructureType*)m_DataStructureTypes[TypeName];

	return NULL;
}


const EnumType *const RuntimeImplementation::GetEnumType(const String &TypeName)
{
	if (m_EnumTypes.ContainsKey(TypeName))
		return (EnumType*)m_EnumTypes[TypeName];

	return NULL;
}


void RuntimeImplementation::RegisterTypeInfo(Type *Type)
{
	if (Type->GetType() == Type::Types::DataStructure)
	{
		String scopedName = Type->GetScopedName();

		if (m_DataStructureTypes.ContainsKey(scopedName))
		{
			LOG_ERROR("Type [" + Type->GetName() + "] already exists")

				return;
		}

		m_DataStructureTypes.Add(scopedName, Type);
	}
	else if (Type->GetType() == Type::Types::Enum)
	{
		const String &name = Type->GetName();

		if (m_EnumTypes.ContainsKey(name))
		{
			LOG_ERROR("Type [" + name + "] already exists")

				return;
		}

		m_EnumTypes.Add(name, Type);
	}
}


void RuntimeImplementation::UnregisterTypeInfo(Type *Type)
{
	if (Type->GetType() == Type::Types::DataStructure)
		m_DataStructureTypes.Remove(Type->GetScopedName());
	else if (Type->GetType() == Type::Types::Enum)
		m_EnumTypes.Remove(Type->GetName());
}


END_NAMESPACE
