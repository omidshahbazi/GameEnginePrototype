// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ENUMTYPE_H
#define ENUMTYPE_H
#include <Public\Type.h>

BEGIN_NAMESPACE

class REFLECTION_API EnumType : public Type
{
public:
	struct Item
	{
	public:
		Item(int32 Value, const String &Name) :
			m_Value(Value),
			m_Name(Name)
		{
		}

	public:
		int32 GetValue(void) const
		{
			return m_Value;
		}

		const String &GetName(void) const
		{
			return m_Name;
		}

	private:
		int32 m_Value;
		String m_Name;
	};

	typedef Vector<Item> ItemsList;

public:
	EnumType(void);
	virtual ~EnumType(void)
	{
	}

	INLINE Types GetType(void) const
	{
		return Types::Enum;
	}

	INLINE const ItemsList &GetItems(void) const
	{
		return m_Items;
	}

protected:
	ItemsList m_Items;
};

END_NAMESPACE

#endif // ENUMTYPE_H
