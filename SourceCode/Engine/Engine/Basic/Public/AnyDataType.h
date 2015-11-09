// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ANYDATATYPE_H
#define ANYDATATYPE_H

#include <Public\Common.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Colour.h>
#include <Public\Matrix4.h>
#include <Public\ValueTypes.h>

BEGIN_NAMESPACE

struct AnyDataType
{
private:
	typedef SmallObjectAllocationPolicy AP;

public:
	AnyDataType(void) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
	}
	AnyDataType(const AnyDataType &Other) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Other;
	}

	AnyDataType(void *Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(bool Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(int8 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(int16 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(int32 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(int64 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(uint8 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(uint16 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(uint32 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(uint64 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(float32 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	//AnyDataType(float64 Value) :
	//	m_Data(NULL),
	//	m_ValueTypes(ValueTypes::None)
	//{
	//	*this = Value;
	//}

	AnyDataType(double32 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(double64 Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(const String &Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(const Vector2 &Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(const Vector3 &Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	AnyDataType(const Matrix4 &Value) :
		m_Data(NULL),
		m_ValueTypes(ValueTypes::None)
	{
		*this = Value;
	}

	~AnyDataType(void)
	{
		if (m_Data)
			AP::Deallocate(m_Data FILE_LINE);
	}

	INLINE AnyDataType &operator= (const AnyDataType &Other)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == Other.m_ValueTypes, "New value should have same type as other's value")

			if (Other.m_ValueTypes != ValueTypes::None)
			{
				uint32 size = GetSize(Other.m_ValueTypes);

				if (m_ValueTypes == ValueTypes::None)
				{
					m_Data = AP::Allocate(size, 1 FILE_LINE);
					m_ValueTypes = Other.m_ValueTypes;
				}

				memcpy(m_Data, Other.m_Data, size);
			}

		return *this;
	}

	INLINE AnyDataType &operator= (void *Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Void, "New value must be a bool")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Void;
				m_Data = AP::Allocate(sizeof(void*), 1 FILE_LINE);
			}

		*(int32*)m_Data = (int32)Value;

		return *this;
	}

	INLINE AnyDataType &operator= (bool Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Bool, "New value must be a bool")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Bool;
				m_Data = AP::Allocate(sizeof(bool), 1 FILE_LINE);
			}

		*(bool*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (int8 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Int8, "New value must be a int8")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Int8;
				m_Data = AP::Allocate(sizeof(int8), 1 FILE_LINE);
			}

		*(int8*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (int16 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Int16, "New value must be a int16")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Int16;
				m_Data = AP::Allocate(sizeof(int16), 1 FILE_LINE);
			}

		*(int16*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (int32 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Int32, "New value must be a int32")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Int32;
				m_Data = AP::Allocate(sizeof(int32), 1 FILE_LINE);
			}

		*(int32*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (int64 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Int64, "New value must be a int64")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Int64;
				m_Data = AP::Allocate(sizeof(int64), 1 FILE_LINE);
			}

		*(int64*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (uint8 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::UInt8, "New value must be a uint8")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::UInt8;
				m_Data = AP::Allocate(sizeof(uint8), 1 FILE_LINE);
			}

		*(uint8*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (uint16 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::UInt16, "New value must be a uint16")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::UInt16;
				m_Data = AP::Allocate(sizeof(uint16), 1 FILE_LINE);
			}

		*(uint16*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (uint32 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::UInt32, "New value must be a uint32")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::UInt32;
				m_Data = AP::Allocate(sizeof(uint32), 1 FILE_LINE);
			}

		*(uint32*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (uint64 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::UInt64, "New value must be a uint64")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::UInt64;
				m_Data = AP::Allocate(sizeof(uint64), 1 FILE_LINE);
			}

		*(uint64*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (float32 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Float32, "New value must be a float32")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Float32;
				m_Data = AP::Allocate(sizeof(float32), 1 FILE_LINE);
			}

		*(float32*)m_Data = Value;

		return *this;
	}

	//INLINE AnyDataType &operator= (float64 Value)
	//{
	//	ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Float64, "New value must be a float64")

	//		if (m_ValueTypes == ValueTypes::None)
	//		{
	//			m_ValueTypes = ValueTypes::Float64;
	//			m_Data = AP::Allocate(sizeof(float64), 1 FILE_LINE);
	//		}

	//	*(float64*)m_Data = Value;

	//	return *this;
	//}

	INLINE AnyDataType &operator= (double32 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Double32, "New value must be a double32")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Double32;
				m_Data = AP::Allocate(sizeof(double32), 1 FILE_LINE);
			}

		*(double32*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (double64 Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Double64, "New value must be a double64")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Double64;
				m_Data = AP::Allocate(sizeof(double64), 1 FILE_LINE);
			}

		*(double64*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (const String &Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::String, "New value must be a String")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::String;
				m_Data = AP::Allocate(sizeof(String), 1 FILE_LINE);
			}

			*(String*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (const Vector2 &Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Vector2, "New value must be a Vector2")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Vector2;
				m_Data = AP::Allocate(sizeof(Vector2), 1 FILE_LINE);
			}

		*(Vector2*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (const Vector3 &Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Vector3, "New value must be a Vector3")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Vector3;
				m_Data = AP::Allocate(sizeof(Vector3), 1 FILE_LINE);
			}

		*(Vector3*)m_Data = Value;

		return *this;
	}

	INLINE AnyDataType &operator= (const Matrix4 &Value)
	{
		ASSERTION(m_ValueTypes == ValueTypes::None || m_ValueTypes == ValueTypes::Matrix4, "New value must be a Matrix4")

			if (m_ValueTypes == ValueTypes::None)
			{
				m_ValueTypes = ValueTypes::Matrix4;
				m_Data = AP::Allocate(sizeof(Matrix4), 1 FILE_LINE);
			}

		*(Matrix4*)m_Data = Value;

		return *this;
	}

	INLINE void *GetAsVoid(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Void, "Value must be a void to get")

			return (void*)*(int32*)m_Data;
	}

	INLINE bool GetAsBool(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Bool, "Value must be a bool to get")

			return *(bool*)m_Data;
	}

	INLINE int8 GetAsInt8(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Int8, "Value must be a int8 to get")

			return *(int8*)m_Data;
	}

	INLINE int16 GetAsInt16(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Int16, "Value must be a int16 to get")

			return *(int16*)m_Data;
	}

	INLINE int32 GetAsInt32(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Int32, "Value must be a int32 to get")

			return *(int32*)m_Data;
	}

	INLINE int64 GetAsInt64(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Int64, "Value must be a int64 to get")

			return *(int64*)m_Data;
	}

	INLINE uint8 GetAsUInt8(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::UInt8, "Value must be a uint8 to get")

			return *(uint8*)m_Data;
	}

	INLINE uint16 GetAsUInt16(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::UInt16, "Value must be a uint16 to get")

			return *(uint16*)m_Data;
	}

	INLINE uint32 GetAsUInt32(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::UInt32, "Value must be a uint32 to get")

			return *(uint32*)m_Data;
	}

	INLINE uint64 GetAsUInt64(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::UInt64, "Value must be a uint64 to get")

			return *(uint64*)m_Data;
	}

	INLINE float32 GetAsFloat32(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Float32, "Value must be a float32 to get")

			return *(float32*)m_Data;
	}

	//INLINE float64 GetAsFloat64(void) const
	//{
	//	ASSERTION(m_ValueTypes == ValueTypes::Float64, "Value must be a float64 to get")

	//		return *(float64*)m_Data;
	//}

	INLINE double32 GetAsDouble32(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Double32, "Value must be a double32 to get")

			return *(double32*)m_Data;
	}

	INLINE double64 GetAsDouble64(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Double64, "Value must be a double64 to get")

			return *(double64*)m_Data;
	}

	INLINE const String &GetAsString(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::String, "Value must be a String to get")

			return *(String*)m_Data;
	}

	INLINE const Vector2 &GetAsVector2(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Vector2, "Value must be a Vector2 to get")

			return *(Vector2*)m_Data;
	}

	INLINE const Vector3 &GetAsVector3(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Vector3, "Value must be a Vector3 to get")

			return *(Vector3*)m_Data;
	}

	INLINE const Matrix4 &GetAsMatrix4(void) const
	{
		ASSERTION(m_ValueTypes == ValueTypes::Matrix4, "Value must be a Matrix4 to get")

			return *(Matrix4*)m_Data;
	}

	INLINE const ValueTypes &GetValueTypes(void) const
	{
		return m_ValueTypes;
	}

private:
	static uint32 GetSize(ValueTypes Type)
	{
		switch (Type)
		{
		case ValueTypes::None:
			return 0;
		case ValueTypes::Void:
			return sizeof(void*);
		case ValueTypes::Bool:
			return sizeof(bool);
		case ValueTypes::UInt8:
			return sizeof(uint8);
		case ValueTypes::UInt16:
			return sizeof(uint16);
		case ValueTypes::UInt32:
			return sizeof(uint32);
		case ValueTypes::UInt64:
			return sizeof(uint64);
		case ValueTypes::Int8:
			return sizeof(int8);
		case ValueTypes::Int16:
			return sizeof(int16);
		case ValueTypes::Int32:
			return sizeof(int32);
		case ValueTypes::Int64:
			return sizeof(int64);
		case ValueTypes::Float32:
			return sizeof(float32);
		case ValueTypes::Float64:
			return sizeof(float64);
		case ValueTypes::Double32:
			return sizeof(double32);
		case ValueTypes::Double64:
			return sizeof(double64);
		case ValueTypes::String:
			return sizeof(String);
		case ValueTypes::Vector2:
			return sizeof(Vector2);
		case ValueTypes::Vector3:
			return sizeof(Vector3);
		case ValueTypes::Matrix4:
			return sizeof(Matrix4);
		}

		return 0;
	}

private:
	void *m_Data;
	ValueTypes m_ValueTypes;
};

END_NAMESPACE
#endif // ANYDATATYPE_H
