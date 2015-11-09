// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PROPERTYTYPE_H
#define PROPERTYTYPE_H
#include <Public\Type.h>
#include <Public\DataType.h>

BEGIN_NAMESPACE

class REFLECTION_API PropertyType : public Type
{
public:
	PropertyType(Type *TopNest) :
		Type(TopNest),
		m_Offset(0)
	{
	}
	PropertyType(Type *TopNest, ValueTypes ValueType) :
		Type(TopNest)
	{
		m_DataType.SetValueType(ValueType);
	}
	virtual ~PropertyType(void)
	{
	}

	INLINE Types GetType(void) const
	{
		return Types::Property;
	}

	INLINE const DataType &GetDataType(void) const
	{
		return m_DataType;
	}

protected:
	uint32 m_Offset;
	DataType m_DataType;
};

END_NAMESPACE

#endif // PROPERTYTYPE_H
