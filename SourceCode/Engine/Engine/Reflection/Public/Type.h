// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TYPE_H
#define TYPE_H
#include <Public\AnyDataType.h>

BEGIN_NAMESPACE

class REFLECTION_API Type
{
public:
	enum class Types
	{
		DataStructure = 0,
		Enum,
		Property,
		Constructor,
		Function
	};

	typedef Vector<Type*> TypesList;

public:
	Type(const String &Name);
	Type(Type *TopNest);
	Type(const String &Name, Type *TopNest);
	virtual ~Type(void)
	{
	}

	INLINE uint32 GetTypeID(void) const
	{
		return m_TypeID;
	}

	virtual Types GetType(void) const = 0;

	INLINE const String &GetName(void) const
	{
		return m_Name;
	}

	INLINE String GetScopedName(void) const
	{
		return (m_TopNest == NULL ? "" : m_TopNest->GetScopedName() + "::") + m_Name;
	}

	INLINE Type *GetTopNest(void)
	{
		return m_TopNest;
	}

protected:
	uint32 m_TypeID;
	String m_Name;
	Type *m_TopNest;
};

typedef List<AnyDataType> ArgumentsList;

END_NAMESPACE

#endif // TYPE_H
