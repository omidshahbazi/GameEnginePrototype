// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MAP_H
#define MAP_H

#include <Public\Allocator.h>
#include <Public\SmallObjectAllocationPolicy.h>

BEGIN_NAMESPACE

template <class K, class V, class AP = SmallObjectAllocationPolicy> class Map
{
public:
	typedef K KeyType;
	typedef V ValueType;

private:
	struct Node : public Allocator<AP>
	{
	public:
		Node(const KeyType &Key) :
			Next(NULL),
			Prev(NULL),
			Key(Key)
		{
		}
		Node(const KeyType &Key, const ValueType &Value) :
			Next(NULL),
			Prev(NULL),
			Key(Key),
			Value(Value)
		{
		}

		Node *Next;
		Node *Prev;
		KeyType Key;
		ValueType Value;
	};

public:
	class ConstIterator;

	class Iterator
	{
	public:
		Iterator(void) :
			m_Current(NULL)
		{
		}

		Iterator(const ConstIterator &Iterator) :
			m_Current(Iterator.m_Current)
		{
		}

	private:
		explicit Iterator(Node *Element) :
			m_Current(Element)
		{
		}

	public:
		INLINE Iterator &operator ++ (void)
		{
			m_Current = m_Current->Next;
			return *this;
		}
		INLINE Iterator &operator -- (void)
		{
			m_Current = m_Current->Prev;
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

		INLINE KeyType &operator * ()
		{
			return m_Current->Key;
		}
		INLINE KeyType *operator -> ()
		{
			return &m_Current->Key;
		}

	private:
		Node *m_Current;

		friend class Map<KeyType, ValueType>;
	};

	class ConstIterator
	{
	public:
		ConstIterator(void) :
			m_Current(NULL)
		{
		}

		ConstIterator(const Iterator &Iterator) :
			m_Current(Iterator.m_Current)
		{
		}

	private:
		explicit ConstIterator(Node *Element) :
			m_Current(Element)
		{
		}

	public:
		INLINE ConstIterator &operator ++ (void)
		{
			m_Current = m_Current->Next;
			return *this;
		}
		INLINE ConstIterator &operator -- (void)
		{
			m_Current = m_Current->Prev;
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

		INLINE ConstIterator &operator += (uint32 Number)
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

		INLINE bool operator == (const Iterator &Other) const
		{
			return (m_Current == Other.m_Current);
		}
		INLINE bool operator != (const Iterator &Other) const
		{
			return (m_Current != Other.m_Current);
		}
		INLINE bool operator == (const ConstIterator &Other) const
		{
			return (m_Current == Other.m_Current);
		}
		INLINE bool operator != (const ConstIterator &Other) const
		{
			return (m_Current != Other.m_Current);
		}

		INLINE const KeyType &operator * ()
		{
			return m_Current->Key;
		}
		INLINE const KeyType *operator -> ()
		{
			return &m_Current->Key;
		}

	private:
		Node *m_Current;

		friend class Map<KeyType, ValueType>;
	};

public:
	Map(void) :
		m_First(NULL),
		m_Last(NULL),
		m_Size(0)
	{
	}

	Map(const Map<KeyType, ValueType> &Other) :
		m_First(NULL),
		m_Last(NULL),
		m_Size(0)
	{
		*this = Other;
	}

	~Map(void)
	{
		Clear();
	}

	INLINE void Clear(void)
	{
		Node *next = NULL;

		while (m_First)
		{
			next = m_First->Next;

			delete m_First;

			m_First = next;
		}

		m_Last = NULL;

		m_Size = 0;
	}

	INLINE bool ContainsKey(const KeyType &Key) const
	{
		if (m_First)
		{
			Node *node = m_First;

			do
			{
				if (node->Key == Key)
					return true;
			} while (node = node->Next);
		}

		return false;
	}

	INLINE ValueType &Add(const KeyType &Key)
	{
		Node *node = NULL;

		if (m_First)
		{
			node = m_First;

			do
			{
				if (node->Key == Key)
					return node->Value;
			} while (node = node->Next);
		}

		node = new Node(Key);

		if (!m_First)
			m_First = node;

		node->Prev = m_Last;

		if (m_Last)
			m_Last->Next = node;

		m_Last = node;

		m_Size++;

		return node->Value;
	}

	INLINE void Add(const KeyType &Key, const ValueType &Value)
	{
		Node *node = NULL;

		if (m_First)
		{
			node = m_First;

			do
			{
				if (node->Key == Key)
					node->Value = Value;
			} while (node = node->Next);
		}

		node = new Node(Key, Value);

		if (!m_First)
			m_First = node;

		node->Prev = m_Last;

		if (m_Last)
			m_Last->Next = node;

		m_Last = node;

		m_Size++;
	}

	INLINE void Remove(const KeyType &Key)
	{
		Node *node = FindIterator(Key).m_Current;

		if (node == m_First)
			m_First = node->Next;
		else if (node->Prev)
			node->Prev->Next = node->Next;

		if (node == m_Last)
			m_Last = node->Prev;
		else if (node->Next)
			node->Next->Prev = node->Prev;

		delete node;

		m_Size--;
	}

	INLINE const Iterator FindIterator(const KeyType &Key)
	{
		Node *node = m_First;

		while (node)
		{
			if (node->Key == Key)
				break;

			node = node->Next;
		}

		if (!node)
			return Iterator(NULL);

		return Iterator(node);
	}

	INLINE const ConstIterator FindIterator(const KeyType &Key) const
	{
		Node *node = m_First;

		while (node)
		{
			if (node->Key == Key)
				break;

			node = node->Next;
		}

		if (!node)
			return GetEnd();

		return ConstIterator(node);
	}

	INLINE void operator = (const Map<KeyType, ValueType> &Other)
	{
		if (this == &Other)
			return;

		Clear();

		Node *node = Other.m_First;

		while (node)
		{
			Add(node->Key);

			node = node->Next;
		}
	}

	INLINE Iterator GetFirst(void)
	{
		return Iterator(m_First);
	}

	INLINE Iterator GetLast(void)
	{
		return Iterator(m_First);
	}

	INLINE Iterator GetEnd(void)
	{
		return Iterator(NULL);
	}

	INLINE ConstIterator GetFirst(void) const
	{
		return ConstIterator(m_First);
	}

	INLINE ConstIterator GetLast(void) const
	{
		return ConstIterator(m_First);
	}

	INLINE ConstIterator GetEnd(void) const
	{
		return ConstIterator(NULL);
	}

	INLINE ValueType &operator [] (const KeyType &Key)
	{
		return Add(Key);
	}

	INLINE const ValueType &operator [] (const KeyType &Key) const
	{
		if (m_First)
		{
			Node *node = m_First;

			do
			{
				if (node->Key == Key)
					return node->Value;
			} while (node = node->Next);
		}

		return GetEnd().m_Current->Value;
	}

	INLINE uint32 GetSize(void) const
	{
		return m_Size;
	}

private:
	Node *m_First;
	Node *m_Last;
	uint32 m_Size;
};

END_NAMESPACE
#endif // MAP_H
