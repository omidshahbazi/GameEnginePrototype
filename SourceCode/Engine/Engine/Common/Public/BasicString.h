// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BASICSTRING_H
#define BASICSTRING_H

#include <Public\SecondaryCommon.h>
#include <Public\SmallObjectAllocationPolicy.h>
#include <Public\List.h>
#include <Public\Allocator.h>
#include <iostream>

BEGIN_NAMESPACE

template <class T, class AP = SmallObjectAllocationPolicy> class BasicString : private Allocator < AP >
{
public:
	typedef T Type;

public:
	BasicString(bool Reserve = false, const uint32 Capacity = 0) :
		m_Buffer(NULL),
		m_Length(0),
		m_Capacity(Capacity)
	{
		if (Reserve && m_Capacity)
			m_Buffer = (T*)AP::Allocate(sizeof(T), m_Capacity + 1 FILE_LINE);
	}
	BasicString(const T Value) :
		m_Buffer(NULL),
		m_Length(0),
		m_Capacity(0)
	{
		*this = Value;
	}
	BasicString(const T *Value, int32 Size = -1) :
		m_Buffer(NULL),
		m_Length(0),
		m_Capacity(0)
	{
		if (Size == -1)
			*this = Value;
		else
		{
			int32 size(Size);

			m_Buffer = (T*)AP::Allocate(sizeof(T), size + 1 FILE_LINE);

			m_Length = m_Capacity = size;

			m_Buffer[m_Length] = NULL_CHARACTER;
			memcpy(m_Buffer, Value, m_Length);
		}
	}
	BasicString(const BasicString<T, AP> &Value) :
		m_Buffer(NULL),
		m_Length(0),
		m_Capacity(0)
	{
		*this = Value;
	}
	~BasicString(void)
	{
		Free();
	}

	INLINE void Reverse(void)
	{
		T temp;

		for (uint32 i = 0; i < m_Length / 2; i++)
		{
			temp = m_Buffer[i];

			m_Buffer[i] = m_Buffer[m_Length - i - 1];

			m_Buffer[m_Length - i - 1] = temp;
		}
	}

	INLINE bool Contains(const T &Value) const
	{
		return Find(Value) != -1;
	}

	INLINE bool Contains(const T *Value) const
	{
		return Find(Value) != -1;
	}

	INLINE bool Contains(const BasicString<T, AP> &Value) const
	{
		return Find(Value) != -1;
	}

	INLINE const int32 Find(const T &Value, uint32 Start = 0) const
	{
		if (m_Length)
		{
			const uint32 pos = std::basic_string<T>(m_Buffer).find(Value, Start);

			if (pos != std::basic_string<T>::npos)
				return pos;
		}

		return -1;
	}
	INLINE const int32 Find(const T *Value, uint32 Start = 0) const
	{
		if (m_Length)
		{
			const uint32 pos = std::basic_string<T>(m_Buffer).find(Value, Start);

			if (pos != std::basic_string<T>::npos)
				return pos;
		}

		return -1;
	}
	INLINE const int32 Find(const BasicString<T, AP> &Value, uint32 Start = 0) const
	{
		return Find(Value.GetBuffer(), Start);
	}

	INLINE const int32 FindFirst(const T &Value, uint32 Start = 0) const
	{
		for (uint32 i = Start; i < m_Length; i++)
			if (m_Buffer[i] == Value)
				return i;

		return -1;
	}
	INLINE const int32 FindFirst(const T *Value, uint32 Start = 0) const
	{
		if (m_Length)
		{
			const uint32 pos = std::basic_string<T>(m_Buffer).find_first_of(Value, Start);

			if (pos != std::basic_string<T>::npos)
				return pos;
		}

		return -1;
	}
	INLINE const int32 FindFirst(const BasicString<T, AP> &Value, uint32 Start = 0) const
	{
		return FindFirst(Value.GetBuffer(), Start);
	}

	INLINE const int32 FindFirstNot(const T *Value, uint32 Start = 0) const
	{
		if (m_Length)
		{
			const uint32 pos = std::basic_string<T>(m_Buffer).find_first_not_of(Value, Start);

			if (pos != std::basic_string<T>::npos)
				return pos;
		}

		return -1;
	}
	INLINE const int32 FindFirstNot(const BasicString<T, AP> &Value, uint32 Start = 0) const
	{
		return FindFirstNot(Value.GetBuffer(), Start);
	}

	INLINE const int32 FindLast(const T &Value, uint32 Start = 0) const
	{
		int32 index = m_Length;

		while (index > 0)
		{
			index--;

			if (m_Buffer[index] == Value)
				return index;
		}

		return -1;
	}
	INLINE const int32 FindLast(const T *Value, uint32 Start = 0) const
	{
		int32 lastValid = -1,
			index = Start - 1;

		while ((index = Find(Value, index + 1)) != -1)
			lastValid = index;

		return lastValid;
	}
	INLINE const int32 FindLast(const BasicString<T, AP> &Value, uint32 Start = 0) const
	{
		return FindLast(Value.GetBuffer(), Start);
	}

	INLINE const int32 FindLastNot(const T *Value, uint32 Start = 0) const
	{
		if (m_Length)
		{
			const uint32 pos = std::basic_string<T>(m_Buffer).find_last_not_of(Value, Start);

			if (pos != std::basic_string<T>::npos)
				return pos;
		}

		return -1;
	}
	INLINE const int32 FindLastNot(const BasicString<T, AP> &Value, uint32 Start = 0) const
	{
		return FindLastNot(Value.GetBuffer(), Start);
	}

	INLINE BasicString<T, AP> SubString(uint32 Start) const
	{
		return SubString(Start, m_Length - Start);
	}
	INLINE BasicString<T, AP> SubString(uint32 Start, uint32 Count) const
	{
		BasicString string;
		string.m_Buffer = (T*)AP::Allocate(sizeof(T), Count + 1 FILE_LINE);
		string.m_Length = Count;

		memcpy(string.m_Buffer, m_Buffer + Start, Count);
		string.m_Buffer[Count] = NULL_CHARACTER;

		return string;
	}

	INLINE void Erase(uint32 Start)
	{
		Erase(Start, m_Length - Start);
	}
	INLINE void Erase(uint32 Start, uint32 Count)
	{
		const uint32 end(Start + Count);
		const uint32 size(m_Length - Count);

		T *newBuffer = (T*)AP::Allocate(sizeof(T), size + 1 FILE_LINE);

		memcpy(newBuffer, m_Buffer, Start + 1);
		memcpy(newBuffer + Start + 1, m_Buffer + end, m_Length - (end + 1));

		AP::Deallocate(m_Buffer FILE_LINE);

		m_Length = size;
		m_Buffer = newBuffer;
	}

	INLINE BasicString<T, AP> Trim(bool Left, bool Right) const
	{
		std::basic_string<T> value(m_Buffer);

		if (Left)
			value.erase(0, value.find_first_not_of(' '));

		if (Right)
			value.erase(value.find_last_not_of(' ') + 1);

		return BasicString<T, AP>(value.c_str()).Remove("\t");
	}
	INLINE BasicString<T, AP> TrimAll(void) const
	{
		return Trim(true, true);
	}
	INLINE BasicString<T, AP> TrimLeft(void) const
	{
		return Trim(true, false);
	}
	INLINE BasicString<T, AP> TrimRight(void) const
	{
		return Trim(false, true);
	}

	INLINE BasicString<T, AP> Remove(const BasicString<T, AP> &What) const
	{
		return Replace(What, BasicString<T, AP>((T*)(""), 0));
	}

	INLINE BasicString<T, AP> Replace(const T &What, const T &With) const
	{
		BasicString<T, AP> string(*this);

		for (uint32 i = 0; i < m_Length; i++)
			if (string.m_Buffer[i] == What)
				string.m_Buffer[i] = With;

		return string;
	}
	INLINE BasicString<T, AP> Replace(const T *What, const T *With) const
	{
		std::basic_string<T> base(m_Buffer);

		const uint32 whatLen = GetStringLenght(What),
			withLen = GetStringLenght(With);

		std::basic_string<T>::size_type start_pos = 0;

		while ((start_pos = base.find(What, start_pos)) != std::basic_string<T>::npos)
		{
			base.replace(start_pos, whatLen, With);
			start_pos += withLen;
		}

		BasicString<T, AP> string(true, base.length());
		string.m_Length = base.length();

		memcpy(string.m_Buffer, base.c_str(), string.m_Length + 1);

		return string;
	}
	INLINE BasicString<T, AP> Replace(const BasicString<T, AP> &What, const BasicString<T, AP> &With) const
	{
		return Replace(What.GetBuffer(), With.GetBuffer());
	}

	INLINE const BasicString<T, AP> &Replace(const T &What, const T &With)
	{
		for (uint32 i = 0; i < m_Length; i++)
			if (m_Buffer[i] == What)
				m_Buffer[i] = With;

		return *this;
	}
	INLINE const BasicString<T, AP> &Replace(const T *What, const T *With)
	{
		std::basic_string<T> base(m_Buffer);

		const uint32 whatLen = GetStringLenght(What),
			withLen = GetStringLenght(With);

		std::basic_string<T>::size_type start_pos = 0;

		while ((start_pos = base.find(What, start_pos)) != std::basic_string<T>::npos)
		{
			base.replace(start_pos, whatLen, With);
			start_pos += withLen;
		}

		m_Length = base.length();

		if (m_Capacity < m_Length)
		{
			Free();
			m_Capacity = m_Length;
			m_Buffer = (T*)AP::Allocate(sizeof(T), m_Length + 1 FILE_LINE);
		}

		memcpy(m_Buffer, base.c_str(), m_Length + 1);

		return *this;
	}
	INLINE const BasicString<T, AP> &Replace(const BasicString<T, AP> &What, const BasicString<T, AP> &With)
	{
		return Replace(What.GetBuffer(), With.GetBuffer());
	}

	INLINE bool StartsWith(const BasicString<T, AP> &Pattern, bool CheckInLowerCase = false) const
	{
		const uint32 patternLen = Pattern.m_Length;

		if (m_Length < patternLen || patternLen == 0)
			return false;

		BasicString<T, AP> startOfThis = SubString(0, patternLen);

		if (CheckInLowerCase)
			startOfThis = startOfThis.ToLowerCase();

		return (startOfThis == Pattern);
	}
	INLINE bool EndsWith(const BasicString<T, AP> &Pattern, bool CheckInLowerCase = false) const
	{
		const uint32 patternLen = Pattern.m_Length;

		if (m_Length < patternLen || patternLen == 0)
			return false;

		BasicString<T, AP> endOfThis = SubString(m_Length - patternLen);

		if (CheckInLowerCase)
			endOfThis = endOfThis.ToLowerCase();

		return (endOfThis == Pattern);
	}

	INLINE List<BasicString<T, AP>> Split(const BasicString<T, AP> &Delimiter) const
	{
		List<BasicString<T, AP>> result;
		std::basic_string<T> s(m_Buffer);
		std::basic_string<T> delimiter(Delimiter.m_Buffer);

		std::size_t pos = 0;
		std::basic_string<T> token;
		while ((pos = s.find(delimiter)) != std::basic_string<T>::npos)
		{
			if (pos != 0)
				result.Add(s.substr(0, pos).c_str());

			s.erase(0, pos + delimiter.length());
		}

		if (s.length() != 0)
			result.Add(s.c_str());

		return result;
	}

	INLINE BasicString<T, AP> ToLowerCase(void) const
	{
		BasicString<T, AP> string(true, m_Length);

		T c;
		for (uint32 i = 0; i < m_Length; i++)
		{
			c = m_Buffer[i];
			string.m_Buffer[i] = (c >= 'A' && c <= 'Z' ? c + 0x20 : c);
		}

		string.m_Buffer[m_Length] = NULL_CHARACTER;
		string.m_Length = m_Length;

		return string;
	}
	INLINE BasicString<T, AP> ToUpperCase(void) const
	{
		if (m_Length == 0)
			return "";

		BasicString<T, AP> string(true, m_Length);

		T c;
		for (uint32 i = 0; i < m_Length; i++)
		{
			c = m_Buffer[i];
			string.m_Buffer[i] = (c >= 'a' && c <= 'z' ? c - 0x20 : c);
		}

		string.m_Buffer[m_Length] = NULL_CHARACTER;
		string.m_Length = m_Length;

		return string;
	}

	INLINE void Clear(void)
	{
		m_Length = 0;
	}

	INLINE T &operator [](uint32 Index)
	{
		//if (Index >= m_Length)
		//THROW_EXCEPTION_AND_RESUME(Exception::ER_INVALID_PARAMETER, "Index is out of bound", "String[]")

		return m_Buffer[Index];
	}
	INLINE const T &operator [](uint32 Index) const
	{
		if (Index >= m_Length)
		{
			//THROW_EXCEPTION_AND_RESUME(Exception::ER_INVALID_PARAMETER, "Index is out of bound", "String[]")

			return NULL_CHARACTER;
		}

		return m_Buffer[Index];
	}

	INLINE BasicString<T, AP> operator +(const T Value) const
	{
		return *this + BasicString<T, AP>(&Value, 1);
	}
	INLINE BasicString<T, AP> operator +(const T *Value) const
	{
		const uint32 size(GetStringLenght(Value));

		BasicString<T, AP> string(true, m_Length + size);
		string.m_Length = m_Length + size;

		memcpy(string.m_Buffer, m_Buffer, m_Length);

		if (size)
			memcpy(string.m_Buffer + m_Length, Value, size + 1);

		return string;
	}
	INLINE BasicString<T, AP> operator +(const BasicString<T, AP> &Value) const
	{
		return *this + Value.GetBuffer();
	}

	template <class U> friend BasicString<U, AP> operator +(const U LeftHand, const BasicString<U, AP> &RightHand);
	template <class U> friend BasicString<U, AP> operator +(const U *LeftHand, const BasicString<U, AP> &RightHand);

	INLINE void operator =(const T Value)
	{
		if (m_Capacity < 1)
		{
			Free();
			m_Capacity = 1;
			m_Buffer = (T*)AP::Allocate(sizeof(T), m_Capacity + 1 FILE_LINE);
		}

		m_Length = 1;

		m_Buffer[0] = Value;
		m_Buffer[1] = NULL_CHARACTER;
	}

	INLINE void operator =(const T *Value)
	{
		const uint32 size = GetStringLenght(Value);

		if (size == 0 || m_Capacity < size)
		{
			Free();
			m_Capacity = size;

			if (m_Capacity != 0)
				m_Buffer = (T*)AP::Allocate(sizeof(T), m_Capacity + 1 FILE_LINE);
		}

		m_Length = size;

		if (m_Length != 0)
			memcpy(m_Buffer, Value, (m_Length * sizeof(T)) + 1);
	}
	INLINE void operator =(const BasicString<T, AP> &Value)
	{
		const uint32 size = Value.m_Length;

		if (size == 0 || m_Capacity < size)
		{
			Free();
			m_Capacity = size;

			if (m_Capacity != 0)
				m_Buffer = (T*)AP::Allocate(sizeof(T), size + 1 FILE_LINE);
		}

		m_Length = size;

		if (m_Length != 0)
			memcpy(m_Buffer, Value.m_Buffer, (m_Length * sizeof(T)) + 1);
	}

	INLINE void operator +=(const T Value)
	{
		*this += &Value;
	}

	INLINE void operator +=(const T *Value)
	{
		const uint32 size(GetStringLenght(Value));

		if (!size)
			return;

		const uint32 len = m_Length + size;

		T *newBuffer;
		if (m_Capacity < len)
		{
			newBuffer = (T*)AP::Allocate(sizeof(T), len + 1 FILE_LINE);
			memcpy(newBuffer, m_Buffer, m_Length);
		}
		else
			newBuffer = m_Buffer;

		memcpy(newBuffer + m_Length, Value, size + 1);

		if (m_Capacity < len)
		{
			Free();
			m_Buffer = newBuffer;
			m_Capacity = len;
		}

		m_Length = len;
	}
	INLINE void operator +=(const BasicString<T, AP> &Value)
	{
		if (!Value.m_Length)
			return;

		const uint32 len = m_Length + Value.m_Length;

		T *newBuffer;
		if (m_Capacity < len)
		{
			newBuffer = (T*)AP::Allocate(sizeof(T), len + 1 FILE_LINE);
			memcpy(newBuffer, m_Buffer, m_Length);
		}
		else
			newBuffer = m_Buffer;

		memcpy(newBuffer + m_Length, Value.m_Buffer, Value.m_Length + 1);

		if (m_Capacity < len)
		{
			Free();
			m_Buffer = newBuffer;
			m_Capacity = len;
		}

		m_Length = len;
	}

	INLINE const bool operator ==(const BasicString<T, AP> &RightHand) const
	{
		if (m_Length != RightHand.m_Length)
			return false;

		uint32 i = m_Length;

		while (i)
		{
			i--;

			if (m_Buffer[i] != RightHand[i])
				return false;
		}

		return true;
	}
	INLINE const bool operator ==(const T *RightHand) const
	{
		return  *this == BasicString<T, AP>(RightHand);
	}
	INLINE const bool operator ==(const T RightHand) const
	{
		if (m_Length != 1 || m_Buffer[0] != RightHand)
			return false;

		return true;
	}


	INLINE const bool operator !=(const BasicString<T, AP> &RightHand) const
	{
		return !(*this == RightHand);
	}
	INLINE const bool operator !=(const T *RightHand) const
	{
		return !(*this == RightHand);
	}
	INLINE const bool operator !=(const T RightHand) const
	{
		return !(*this == RightHand);
	}

	template <class TU, class APU> friend std::basic_ostream<TU> &operator <<(std::basic_ostream<TU> &Stream, const BasicString<TU, APU> &Value);
	template <class TU, class APU> friend bool operator ==(const TU *Left, const BasicString<TU, APU> &Right);
	template <class TU, class APU> friend bool operator !=(const TU *Left, const BasicString<TU, APU> &Right);

	INLINE const T *GetBuffer(void) const
	{
		return m_Buffer;
	}

	INLINE const uint32 GetLength(void) const
	{
		return m_Length;
	}

	INLINE const uint32 GetCapacity(void) const
	{
		return m_Capacity;
	}

private:
	INLINE void Free(void)
	{
		if (m_Length)
		{
			AP::Deallocate(m_Buffer FILE_LINE);
			m_Length = 0;
			m_Capacity = 0;
		}
	}

	INLINE static const uint32 GetStringLenght(const T *Value)
	{
		if (!Value)
			return 0;

		uint32 index = 0;

		while (Value[index]) index++;

		return index;
		//return index != 0 ? index / sizeof(T) : 0;
	}

private:
	static const char NULL_CHARACTER = '\0';

	T *m_Buffer;
	uint32 m_Length;
	uint32 m_Capacity;

public:
	static const BasicString<char> EMPTY;
};

template <class TU, class APU> BasicString<TU, APU> operator + (const TU LeftHand, const BasicString<TU, APU> &RightHand)
{
	return BasicString<TU, APU>(&LeftHand, 1) + RightHand;
}

template <class TU, class APU> BasicString<TU, APU> operator + (const TU *LeftHand, const BasicString<TU, APU> &RightHand)
{
	return BasicString<TU, APU>(LeftHand) +RightHand;
}

template <class TU, class APU> std::basic_ostream<TU> &operator <<(std::basic_ostream<TU> &Stream, const BasicString<TU, APU> &Value)
{
	if (Value.m_Length)
		Stream << Value.m_Buffer;

	return Stream;
}

template <class TU, class APU> bool operator ==(const TU *Left, const BasicString<TU, APU> &Right)
{
	return (Right == Left);
}

template <class TU, class APU> bool operator !=(const TU *Left, const BasicString<TU, APU> &Right)
{
	return (Right != Left);
}

END_NAMESPACE
#endif // BASICSTRING_H
