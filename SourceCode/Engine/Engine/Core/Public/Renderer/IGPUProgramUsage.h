// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGPUPROGRAMUSAGE_H
#define IGPUPROGRAMUSAGE_H

#include <Public\Renderer\IGPUProgram.h>
#include <Public\HashMap.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Colour.h>
#include <Public\Matrix4.h>

BEGIN_NAMESPACE

struct Vector2;
struct Vector3;
struct Matrix4;

enum class BasicDataTypes
{
	Unknown = 0,
	Boolean,
	Integer,
	Float
};

class IGPUProgramUsage
{
public:
	struct Parameter
	{
	public:
		Parameter(void) :
			m_Data(NULL),
			m_DataType(BasicDataTypes::Unknown),
			m_Count(0)
		{
		}
		Parameter(const Parameter &Other) :
			m_Data(NULL)
		{
			*this = Other;
		}

		~Parameter(void)
		{
			if (m_Data)
				delete m_Data;
		}

		INLINE void SetData(bool Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 1 && m_DataType == BasicDataTypes::Boolean, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Boolean;
				m_Count = 1;
				m_Data = malloc(sizeof(bool)* m_Count);
			}

			memcpy(m_Data, &Data, sizeof(bool));
		}
		INLINE void SetData(int32 Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 1 && m_DataType == BasicDataTypes::Integer, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Integer;
				m_Count = 1;
				m_Data = malloc(sizeof(int32));
			}

			memcpy(m_Data, &Data, sizeof(int32));
		}
		INLINE void SetData(float32 Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 1 && m_DataType == BasicDataTypes::Float, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Float;
				m_Count = 1;
				m_Data = malloc(sizeof(float32));
			}

			memcpy(m_Data, &Data, sizeof(float32));
		}
		INLINE void SetData(const Vector2 &Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 2 && m_DataType == BasicDataTypes::Float, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Float;
				m_Count = 2;
				m_Data = malloc(sizeof(float32)* m_Count);
			}

			float32 *pointer = (float32*)m_Data;
			memcpy(pointer, &Data.X, sizeof(float32));
			memcpy(pointer++, &Data.Y, sizeof(float32));
		}
		INLINE void SetData(const Vector3 &Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 3 && m_DataType == BasicDataTypes::Float, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Float;
				m_Count = 3;
				m_Data = malloc(sizeof(float)* m_Count);
			}

			float32 *pointer = (float32*)m_Data;
			memcpy(pointer, &Data.X, sizeof(float32));
			memcpy(pointer++, &Data.Y, sizeof(float32));
			memcpy(pointer++, &Data.Z, sizeof(float32));
		}
		INLINE void SetData(const Colour &Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 4 && m_DataType == BasicDataTypes::Float, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Float;
				m_Count = 4;
				m_Data = malloc(sizeof(float32)* m_Count);
			}

			float32 *pointer = (float32*)m_Data;
			*pointer = Data.GetRed() / 255.0F;
			*(pointer++) = Data.GetGreen() / 255.0F;
			*(pointer++) = Data.GetBlue() / 255.0F;
			*(pointer++) = Data.GetAlpha() / 255.0F;
		}
		INLINE void SetData(const Matrix4 &Data)
		{
			if (m_Data)
				ASSERTION(m_Count == 16 && m_DataType == BasicDataTypes::Float, "New value should have save count and type as previous value")
			else
			{
				m_DataType = BasicDataTypes::Float;
				m_Count = 16;
				m_Data = malloc(sizeof(float32)* m_Count);
			}

			memcpy(m_Data, Data.GetPointer(), sizeof(float32)* m_Count);
		}

		INLINE const void *GetData(void) const
		{
			return m_Data;
		}

		INLINE const BasicDataTypes &GetDataType(void) const
		{
			return m_DataType;
		}

		INLINE uint32 GetCount(void) const
		{
			return m_Count;
		}

		INLINE Parameter &operator= (bool Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (int32 Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (float32 Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (const Vector2 &Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (const Vector3 &Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (const Colour &Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (const Matrix4 &Data)
		{
			SetData(Data);

			return *this;
		}
		INLINE Parameter &operator= (const Parameter &Other)
		{
			if (m_Data)
				ASSERTION(m_Count == Other.m_Count && m_DataType == Other.m_DataType, "New value should have save count and type as previous value")
			else
			{
				m_DataType = Other.m_DataType;
				m_Count = Other.m_Count;
				m_Data = malloc((int32)m_DataType * m_Count);
			}

			memcpy(m_Data, Other.m_Data, (int32)m_DataType * m_Count);

			return *this;
		}

	private:
		void *m_Data;
		BasicDataTypes m_DataType;
		uint32 m_Count;
	};

public:
	typedef HashMap<String, Parameter> ParamMap;

public:
	virtual ~IGPUProgramUsage(void) {}

	virtual void ClearAutoParams(void) = 0;
	virtual void SetAutoParam(const String &Constant, const String &Param) = 0;

	virtual void ClearParams(void) = 0;
	virtual void SetBool(const String &Name, bool Value) = 0;
	virtual void SetInteger(const String &Name, int32 Value) = 0;
	virtual void SetFloat(const String &Name, float32 Value) = 0;
	virtual void SetVector2(const String &Name, const Vector2 &Value) = 0;
	virtual void SetVector3(const String &Name, const Vector3 &Value) = 0;
	virtual void SetColour(const String &Name, const Colour &Value) = 0;
	virtual void SetMatrix(const String &Name, const Matrix4 &Value) = 0;

	virtual IGPUProgram *GetProgram(void) const = 0;

	virtual bool HasProgram(void) const = 0;
};

END_NAMESPACE
#endif // IGPUPROGRAMUSAGE_H
