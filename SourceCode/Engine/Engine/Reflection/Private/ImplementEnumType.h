// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMPLEMENTENUMTYPE_H
#define IMPLEMENTENUMTYPE_H
#include <Public\EnumType.h>

BEGIN_NAMESPACE

class REFLECTION_API ImplementEnumType : public EnumType
{
public:
	ImplementEnumType(void);
	virtual ~ImplementEnumType(void)
	{
	}

	INLINE void SetName(const String &Value)
	{
		m_Name = Value;
	}

	INLINE void AddItem(const String &Value)
	{
		m_Items.Add(Item(0, Value));
	}

	INLINE void AddItem(int32 Value, const String &Name)
	{
		m_Items.Add(Item(Value, Name));
	}
};

END_NAMESPACE
#endif // IMPLEMENTENUMTYPE_H
