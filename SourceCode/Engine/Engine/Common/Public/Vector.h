// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VECTOR_H
#define VECTOR_H

#include <Public\SecondaryCommon.h>
#include <Public\SmallObjectAllocationPolicy.h>

BEGIN_NAMESPACE

template <class T, class AP = SmallObjectAllocationPolicy> class Vector
{
public:
	typedef T Type;

public:
	class ConstIterator;

	class Iterator
	{
	public:
		Iterator(void) :
			m_Vector(NULL),
			m_Current(-1)
		{
		}

		Iterator(const ConstIterator &Iterator) :
			m_Current(Iterator.m_Current)
		{
		}

	private:
		explicit Iterator(Vector<T, AP> *Vector, int32 ItemIndex) :
			m_Vector(Vector),
			m_Current(ItemIndex)
		{
		}

	public:
		INLINE Iterator &operator ++ (void)
		{
			if (m_Current + 1 == m_Vector->m_Size)
				m_Current = -1;
			else
				m_Current++;

			return *this;
		}
		INLINE Iterator &operator -- (void)
		{
			if (m_Current - 1 == -1)
				m_Current = -1;
			else
				m_Current = (m_Current - 1);

			return *this;
		}
		INLINE Iterator &operator ++ (int32)
		{
			return ++*this;
		}
		INLINE Iterator &operator -- (int32)
		{
			return --*this;
		}

		INLINE Iterator &operator +=(uint32 Number)
		{
			if (Number > 0)
			{
				while (Number-- && m_Current)
					this->operator++();
			}
			else
			{
				while (Number++ && m_Current)
					this->operator--();
			}

			return *this;
		}
		INLINE Iterator &operator -= (uint32 Number)
		{
			return this->operator+=(-Number);
		}

		INLINE bool operator ==(const Iterator &Other) const
		{
			return (m_Current == Other.m_Current);
		}
		INLINE bool operator !=(const Iterator &Other) const
		{
			return (m_Current != Other.m_Current);
		}

		INLINE T *operator * ()
		{
			return &m_Vector->m_Buffer[m_Current];
		}
		INLINE T &operator & ()
		{
			return m_Vector->m_Buffer[m_Current];
		}
		INLINE T &operator -> ()
		{
			return m_Vector->m_Buffer[m_Current];
		}

	private:
		Vector<T, AP> *m_Vector;
		int32 m_Current;

		friend class Vector < T, AP > ;
	};

	class ConstIterator
	{
	private:
		ConstIterator(const Vector<T, AP> *Target, int32 ItemIndex) :
			m_Vector(const_cast<Vector<T, AP>*>(Target)),
			m_Current(ItemIndex)
		{
		}

		ConstIterator(const Iterator &Iterator) :
			m_Current(Iterator.m_Current)
		{
		}

	public:
		INLINE ConstIterator &operator ++ (void)
		{
			if (m_Current + 1 == m_Vector->m_Size)
				m_Current = -1;
			else
				m_Current++;

			return *this;
		}
		INLINE ConstIterator &operator -- (void)
		{
			if (m_Current - 1 == -1)
				m_Current = -1;
			else
				m_Current = (m_Current - 1);

			return *this;
		}
		INLINE ConstIterator &operator ++ (int32)
		{
			return ++*this;
		}
		INLINE ConstIterator &operator -- (int32)
		{
			return --*this;
		}

		INLINE ConstIterator &operator +=(uint32 Number)
		{
			if (Number > 0)
			{
				while (Number-- && m_Current)
					this->operator++();
			}
			else
			{
				while (Number++ && m_Current)
					this->operator--();
			}

			return *this;
		}
		INLINE ConstIterator &operator -= (uint32 Number)
		{
			return this->operator+=(-Number);
		}

		INLINE bool operator ==(const ConstIterator &Other) const
		{
			return (m_Current == Other.m_Current);
		}
		INLINE bool operator !=(const ConstIterator &Other) const
		{
			return (m_Current != Other.m_Current);
		}

		INLINE T *operator * ()
		{
			return &m_Vector->m_Buffer[m_Current];
		}
		INLINE const T &operator & ()
		{
			return m_Vector->m_Buffer[m_Current];
		}
		INLINE const T &operator -> ()
		{
			return m_Vector->m_Buffer[m_Current];
		}


		friend class Vector < T, AP > ;
	private:
		Vector<T, AP> *m_Vector;
		int32 m_Current;
	};

public:
	Vector(uint32 Capacity = 0) :
		m_Buffer(NULL),
		m_Size(0),
		m_Capacity(Capacity)
	{
		if (m_Capacity)
			m_Buffer = (T*)AP::Allocate(sizeof(T), m_Capacity FILE_LINE);
	}

	Vector(const Vector<T, AP> &Other) :
		m_Buffer(NULL),
		m_Size(0),
		m_Capacity(0)
	{
		*this = Other;
	}

	~Vector(void)
	{
		Free();
	}

	INLINE void Clear(void)
	{
		m_Size = 0;
	}

	INLINE void Add(const T &Value)
	{
		if (m_Capacity <= m_Size)
		{
			T *buffer = (T*)AP::Allocate(sizeof(T), m_Size + 1 FILE_LINE);

			uint32 i;
			for (i = 0; i < m_Size; i++)
				buffer[i] = m_Buffer[i];

			Free();

			m_Buffer = buffer;
			m_Size = m_Capacity = i + 1;
		}
		else
			m_Size++;

		m_Buffer[m_Size - 1] = Value;
	}

	INLINE void Add(const Vector<T, AP> &Other)
	{
		if (!Other.m_Size)
			return;

		if (m_Capacity < m_Size + Other.m_Size)
		{
			T *buffer = (T*)AP::Allocate(sizeof(T), m_Size + Other.m_Size FILE_LINE);

			uint32 i;
			for (i = 0; i < m_Size; i++)
				buffer[i] = m_Buffer[i];

			Free();

			m_Buffer = buffer;
			m_Size = i;
			m_Capacity = m_Size + Other.m_Size;
		}

		for (uint32 i = 0; i < Other.m_Size; i++)
			m_Buffer[m_Size + i] = Other.m_Buffer[i];

		m_Size += Other.m_Size;
	}

	INLINE void Insert(uint32 Index, const T &Value)
	{
		uint32 i;
		if (m_Capacity <= m_Size)
		{
			T *buffer = (T*)AP::Allocate(sizeof(T), m_Size + 1 FILE_LINE);

			for (i = 0; i < Index; i++)
				buffer[i] = m_Buffer[i];

			buffer[Index] = Value;

			for (i = Index; i < m_Size; i++)
				buffer[i + 1] = m_Buffer[i];

			Free();

			m_Size = m_Capacity = i + 1;
			m_Buffer = buffer;
		}
		else
		{
			for (i = m_Size; i > Index; i--)
				m_Buffer[i] = m_Buffer[i - 1];

			m_Buffer[Index] = Value;

			m_Size++;
		}
	}

	INLINE void RemoveAt(uint32 Index)
	{
		if (Index >= m_Size)
			return;

		m_Size--;

		for (uint32 i = Index; i < m_Size; i++)
			m_Buffer[i] = m_Buffer[i + 1];
	}

	INLINE void Remove(const T &Item)
	{
		int32 index = 0;
		while ((index = FindIndex(Item, index)) != -1)
			RemoveAt(index);
	}

	INLINE void Remove(const Iterator &Item)
	{
		if (Item == GetEnd())
			return;

		RemoveAt(Item.m_Current);
	}

	INLINE int32 FindIndex(const T &Item, uint32 StartIndex = 0) const
	{
		for (uint32 i = StartIndex; i < m_Size; i++)
			if (m_Buffer[i] == Item)
				return i;

		return -1;
	}

	INLINE const Iterator FindIterator(const T &Item)
	{
		const int32 index = Find(Item);

		if (index > -1)
			return Iterator(this, index);

		return GetEnd();
	}

	INLINE T &GetItem(uint32 Index)
	{
		//if (m_Size <= Index)
		//	THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "Index is out of bounding of List", "")

		return m_Buffer[Index];
	}

	INLINE const T &GetItem(uint32 Index) const
	{
		return m_Buffer[Index];
	}

	INLINE void operator =(const Vector<T, AP> &Other)
	{
		if (m_Capacity < Other.m_Size)
		{
			Free();

			m_Buffer = (T*)AP::Allocate(sizeof(T), m_Size FILE_LINE);
			m_Capacity = Other.m_Size;
		}

		m_Size = Other.m_Size;

		int32 index = m_Size - 1;

		while (index >= 0)
		{
			m_Buffer[index] = Other[index];
			index--;
		}
	}

	INLINE T &operator [](uint32 Index) const
	{
		return m_Buffer[Index];
	}

	INLINE Iterator GetFirst(void)
	{
		if (!m_Size)
			return GetEnd();

		return Iterator(this, 0);
	}

	INLINE Iterator GetLast(void)
	{
		if (!m_Size)
			return GetEnd();

		return Iterator(this, m_Size - 1);
	}

	INLINE Iterator GetEnd(void)
	{
		return Iterator(this, -1);
	}

	INLINE ConstIterator GetFirst(void) const
	{
		if (!m_Size)
			return GetEnd();

		return ConstIterator(this, 0);
	}

	INLINE ConstIterator GetLast(void) const
	{
		if (!m_Size)
			return GetEnd();

		return ConstIterator(this, m_Size - 1);
	}

	INLINE ConstIterator GetEnd(void) const
	{
		return ConstIterator(this, -1);
	}

	INLINE uint32 GetSize(void) const
	{
		return m_Size;
	}

	INLINE uint32 GetCapacity(void) const
	{
		return m_Capacity;
	}

protected:
	void Free(void)
	{
		if (m_Size)
		{
			AP::Deallocate(m_Buffer FILE_LINE);
			m_Size = 0;
			m_Capacity = 0;
		}
	}

protected:
	T *m_Buffer;
	uint32 m_Size;
	uint32 m_Capacity;
};

END_NAMESPACE
#endif // VECTOR_H
