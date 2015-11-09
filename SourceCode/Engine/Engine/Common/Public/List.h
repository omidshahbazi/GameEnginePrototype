// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LIST_H
#define LIST_H

#include <Public\Allocator.h>
#include <Public\SmallObjectAllocationPolicy.h>

BEGIN_NAMESPACE

template <class T, class AP = SmallObjectAllocationPolicy> class List
{
public:
	typedef T Type;

private:
	struct Node : public Allocator < AP >
	{
	public:
		Node(const T &Value) :
			Next(NULL),
			Prev(NULL),
			Item(Value)
		{
		}

		Node *Next;
		Node *Prev;
		T Item;
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

		INLINE 	T &operator * ()
		{
			return m_Current->Item;
		}
		INLINE	T *operator -> ()
		{
			return &m_Current->Item;
		}

	private:
		Node *m_Current;

		friend class List < T > ;
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

		INLINE const T &operator * () const
		{
			return m_Current->Item;
		}
		INLINE const T *operator -> () const
		{
			return &m_Current->Item;
		}

	private:
		Node *m_Current;

		friend class List < T > ;
	};

public:
	List(void) :
		m_First(NULL),
		m_Last(NULL),
		m_Size(0)
	{
	}

	List(const List<T> &Other) :
		m_First(NULL),
		m_Last(NULL),
		m_Size(0)
	{
		*this = Other;
	}

	~List(void)
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

	INLINE void Add(const T &Item)
	{
		m_Size++;

		Node *node = new Node(Item);

		if (!m_First)
			m_First = node;

		node->Prev = m_Last;

		if (m_Last)
			m_Last->Next = node;

		m_Last = node;
	}

	INLINE void Add(const List<T> &Other)
	{
		for (List<T>::ConstIterator it = Other.GetFirst(), end = Other.GetEnd(); it != end; it++)
			Add(*it);
	}

	INLINE void Insert(uint32 Index, const T &Item)
	{
		//if (Index >= m_Size)
		//	THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "Index is out of bounding of List", "")

		Node *node = m_First;

		uint32 i = Index;

		while (i)
		{
			i--;
			node = node->Next;
		}

		Node *newNode = new Node(Item);

		newNode->Prev = node->Prev;
		newNode->Next = node;

		if (node->Prev)
			node->Prev->Next = newNode;

		node->Prev = newNode;

		m_Size++;



		//if (Index >= m_Size)
		//	THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "Index is out of bounding of List", "")

		//Element *elem = m_First;

		//uint32 i = Index - 1;

		//while (i)
		//{
		//	i--;
		//	elem = elem->Next;
		//}

		//Element *newElem = new Element(Item);

		//newElem->Prev = elem;
		//newElem->Next = elem->Next;

		//if (elem->Next)
		//	elem->Next->Prev = newElem;

		//elem->Next = newElem;
		//
		//m_Size++;
	}

	INLINE void RemoveAt(uint32 Index)
	{
		if (Index >= m_Size)
			return;

		Node *node = m_First;

		uint32 i = Index;

		while (i)
		{
			i--;
			node = node->Next;
		}

		if (node->Prev)
			node->Prev->Next = node->Next;

		if (node->Next)
			node->Next->Prev = node->Prev;

		delete node;

		m_Size--;
	}

	INLINE void Remove(const T &Item)
	{
		Iterator it;
		while ((it = FindIterator(Item)) != GetEnd())
			Remove(it);
	}

	INLINE void Remove(const Iterator &Item)
	{
		if (Item == GetEnd())
			return;

		Node *node = Item.m_Current;

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

	INLINE uint32 FindIndex(const T &Item) const
	{
		Node *node = m_Last;

		int32 i = m_Size - 1;

		while (node->Item != Item && i > -1)
		{
			node = node->Prev;
			i--;

			if (!node)
				return -1;
		}

		return i;
	}

	INLINE Iterator FindIterator(const T &Item)
	{
		Node *node = m_First;

		while (node)
		{
			if (node->Item == Item)
				break;

			node = node->Next;
		}

		if (!node)
			return GetEnd();

		return Iterator(node);
	}

	INLINE const ConstIterator FindIterator(const T &Item) const
	{
		Node *node = m_First;

		while (node)
		{
			if (node->Item == Item)
				break;

			node = node->Next;
		}

		if (!node)
			return GetEnd();

		return ConstIterator(node);
	}

	INLINE T &GetItem(uint32 Index)
	{
		//if (m_Size <= Index)
		//	THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "Index is out of bounding of List", "")

		Node *node = m_First;

		uint32 i = Index;

		while (i)
		{
			i--;
			node = node->Next;
		}

		return node->Item;
	}

	INLINE const T &GetItem(uint32 Index) const
	{
		//if (m_Size <= Index)
		//	THROW_EXCEPTION_AND_STOP(Exception::ER_INVALID_PARAMETER, "Index is out of bounding of List", "")

		Node *node = m_First;

		uint32 i = Index;

		while (i)
		{
			i--;
			node = node->Next;
		}

		return node->Item;
	}

	INLINE void operator = (const List<T> &Other)
	{
		if (this == &Other)
			return;

		Clear();

		Node *node = Other.m_First;

		while (node)
		{
			Add(node->Item);

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

	INLINE T &operator [] (uint32 Index)
	{
		return GetItem(Index);
	}

	INLINE const T &operator [] (uint32 Index) const
	{
		return GetItem(Index);
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
#endif // LIST_H
