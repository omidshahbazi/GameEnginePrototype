// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMPLEMENTDATASTRUCTURETYPE_H
#define IMPLEMENTDATASTRUCTURETYPE_H
#include <Public\DataStructureType.h>

BEGIN_NAMESPACE

class REFLECTION_API ImplementDataStructureType : public DataStructureType
{
public:
	ImplementDataStructureType(DataStructureType *TopNest);
	virtual ~ImplementDataStructureType(void)
	{
	}

	INLINE void AddSubType(Type *Value, AccessSpecifiers Access)
	{
		if (Access == AccessSpecifiers::None || Access == AccessSpecifiers::Private)
			m_NonPublicSubTypes.Add(Value);
		else
			m_PublicSubTypes.Add(Value);
	}

	INLINE void AddFunction(Type *Value, AccessSpecifiers Access)
	{
		if (Access == AccessSpecifiers::None || Access == AccessSpecifiers::Private)
			m_NonPublicFunctions.Add(Value);
		else
			m_PublicFunctions.Add(Value);
	}

	INLINE void AddProperty(Type *Value, AccessSpecifiers Access)
	{
		if (Access == AccessSpecifiers::None || Access == AccessSpecifiers::Private)
			m_NonPublicProperties.Add(Value);
		else
			m_PublicProperties.Add(Value);
	}

	INLINE 	void SetName(const String &Value)
	{
		m_Name = Value;
	}
};

END_NAMESPACE

#endif // IMPLEMENTDATASTRUCTURETYPE_H
