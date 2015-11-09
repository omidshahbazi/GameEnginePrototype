// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ARGUMENTSPARSER_H
#define ARGUMENTSPARSER_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class BASIC_API ArgumentsParser
{
public:
	ArgumentsParser(uint8 Count, const char **Arguments, bool FirstIsAddress = true);

	INLINE const String &GetAddress(void) const
	{
		return m_Address;
	}

	INLINE const String &GetAsString(uint8 Index) const
	{
		ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return m_Arguments[Index];
	}
	
	int8 GetAsInt8(uint8 Index) const;
	int16 GetAsInt16(uint8 Index) const;
	int32 GetAsInt32(uint8 Index) const;
	int64 GetAsInt64(uint8 Index) const;

	uint8 GetAsUInt8(uint8 Index) const;
	uint16 GetAsUInt16(uint8 Index) const;
	uint32 GetAsUInt32(uint8 Index) const;
	uint64 GetAsUInt64(uint8 Index) const;

	float32 GetAsFloat32(uint8 Index) const;

	const String &GetAsString(const String &Parameter) const;

	int8 GetAsInt8(const String &Parameter) const;
	int16 GetAsInt16(const String &Parameter) const;
	int32 GetAsInt32(const String &Parameter) const;
	int64 GetAsInt64(const String &Parameter) const;

	uint8 GetAsUInt8(const String &Parameter) const;
	uint16 GetAsUInt16(const String &Parameter) const;
	uint32 GetAsUInt32(const String &Parameter) const;
	uint64 GetAsUInt64(const String &Parameter) const;

	float32 GetAsFloat32(const String &Parameter) const;

	INLINE bool Has(const String &Parameter) const
	{
		return m_Arguments.FindIndex(Parameter) != -1;
	}

	INLINE uint8 GetCount(void) const
	{
		return m_Arguments.GetSize();
	}

private:
	String m_Address;
	StringsList m_Arguments;
};

END_NAMESPACE
#endif // ARGUMENTSPARSER_H
