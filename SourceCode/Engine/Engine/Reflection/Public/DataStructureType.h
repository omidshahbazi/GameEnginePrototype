// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef DATASTRUCTURETYPE_H
#define DATASTRUCTURETYPE_H
#include <Public\Type.h>
#include <Public\FunctionType.h>

BEGIN_NAMESPACE

enum class AccessSpecifiers
{
	None = 0,
	Private,
	Protected,
	Public,

	Count
};

class REFLECTION_API DataStructureType : public Type
{
public:
	DataStructureType(Type *TopNest) :
		Type(TopNest)
	{
	}
	virtual ~DataStructureType(void)
	{
	}

	INLINE Types GetType(void) const
	{
		return Types::DataStructure;
	}

	INLINE const TypesList &GetPublicSubTypes(void) const
	{
		return m_PublicSubTypes;
	}

	INLINE const TypesList &GetNonPublicSubTypes(void) const
	{
		return m_NonPublicSubTypes;
	}

	INLINE const TypesList &GetPublicFunction(void) const
	{
		return m_PublicFunctions;
	}

	INLINE const TypesList &GetNonPublicFunction(void) const
	{
		return m_NonPublicFunctions;
	}

	INLINE const FunctionType *const GetFunction(const String &Name, AccessSpecifiers Access = AccessSpecifiers::Public) const
	{
		FOR_EACH(type, (Access == AccessSpecifiers::Public ? m_PublicFunctions : m_NonPublicFunctions))
			if (type->GetName() == Name)
				return (FunctionType*)&type;

		return NULL;
	}

	INLINE const TypesList &GetPublicProperties(void) const
	{
		return m_PublicProperties;
	}

	INLINE const TypesList &GetNonPublicProperties(void) const
	{
		return m_NonPublicProperties;
	}

	AnyDataType CreateInstance(void) const;
	AnyDataType CreateInstance(const AnyDataType &Argument) const;
	AnyDataType CreateInstance(const ArgumentsList &Arguments) const;

protected:
	virtual void CreateInstanceInternal(AnyDataType &ReturnValue, const ArgumentsList *Arguments) const = 0;

protected:
	TypesList m_PublicSubTypes;
	TypesList m_NonPublicSubTypes;
	TypesList m_PublicFunctions;
	TypesList m_NonPublicFunctions;
	TypesList m_PublicProperties;
	TypesList m_NonPublicProperties;
};

END_NAMESPACE

#endif // DATASTRUCTURETYPE_H
