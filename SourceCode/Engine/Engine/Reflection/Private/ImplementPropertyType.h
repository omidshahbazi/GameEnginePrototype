// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMPLEMENTPROPERTYTYPE_H
#define IMPLEMENTPROPERTYTYPE_H
#include <Public\PropertyType.h>

BEGIN_NAMESPACE

class REFLECTION_API ImplementPropertyType : public PropertyType
{
public:
	ImplementPropertyType(Type *TopNest);
	virtual ~ImplementPropertyType(void)
	{
	}

	INLINE 	void SetName(const String &Value)
	{
		m_Name = Value;
	}

	INLINE void SetDataType(const DataType &Value)
	{
		m_DataType = Value;
	}

	INLINE uint32 GetOffset(void) const
	{
		return m_Offset;
	}
	INLINE void SetOffset(uint32 Value)
	{
		m_Offset = Value;
	}
};

END_NAMESPACE

#endif // IMPLEMENTPROPERTYTYPE_H
