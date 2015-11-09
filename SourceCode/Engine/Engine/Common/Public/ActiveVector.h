// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ACTIVEVECTOR_H
#define ACTIVEVECTOR_H

#include <Public\Vector.h>

BEGIN_NAMESPACE

template <class T, class AP = SmallObjectAllocationPolicy> class ActiveVector
{
public:
	ActiveVector(uint32 Capacity = 0) :
		m_Vector(Capacity),
		m_ActiveCount(0)
	{
	}

	INLINE void Add(const T &Value)
	{
		m_Vector.Insert(m_ActiveCount++, Value);
	}

	INLINE void Remove(const T &Value)
	{
		int32 index = m_Vector.FindIndex(Value);

		if (index < m_ActiveCount)
			m_ActiveCount--;

		m_Vector.RemoveAt(index);
	}

	INLINE void SetActive(const T &Item, bool Value)
	{
		const int32 i = m_Vector.FindIndex(Item);

		ASSERTION(i > -1, "Item doesn't added")

		uint32 swapWith;

		if (Value)
		{
			swapWith = m_ActiveCount;

			m_ActiveCount++;
		}
		else
		{
			m_ActiveCount--;

			swapWith = m_ActiveCount;
		}

		if (i == swapWith)
			return;

		T temp = m_Vector[m_ActiveCount];
		m_Vector[m_ActiveCount] = m_Vector[i];
		m_Vector[i] = temp;
	}

	INLINE T &operator [](uint32 Index) const
	{
		return m_Vector[Index];
	}

	INLINE uint32 GetSize(void) const
	{
		return m_Vector.GetSize();
	}

	INLINE uint32 GetActiveCount(void) const
	{
		return m_ActiveCount;
	}

	INLINE uint32 GetInactiveCount(void) const
	{
		return m_Vector.GetSize() - m_ActiveCount;
	}

	INLINE uint32 GetInactiveStartIndex(void) const
	{
		return m_ActiveCount;
	}

private:
	Vector<T, AP> m_Vector;
	uint32 m_ActiveCount;
};

END_NAMESPACE
#endif // ACTIVEVECTOR_H
