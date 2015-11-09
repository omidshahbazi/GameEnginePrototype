// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\ArgumentsParser.h>
#include <Public\StringConverter.h>

BEGIN_NAMESPACE


ArgumentsParser::ArgumentsParser(uint8 Count, const char **Arguments, bool FirstIsAddress)
{
	if (FirstIsAddress && Count != 0)
		m_Address = Arguments[0];

	for (uint8 i = FirstIsAddress ? 1 : 0; i < Count; i++)
		m_Arguments.Add(String(Arguments[i]).TrimAll());
}


int8 ArgumentsParser::GetAsInt8(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseInt8(m_Arguments[Index]);
}


int16 ArgumentsParser::GetAsInt16(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseInt16(m_Arguments[Index]);
}


int32 ArgumentsParser::GetAsInt32(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseInt32(m_Arguments[Index]);
}


int64 ArgumentsParser::GetAsInt64(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseInt64(m_Arguments[Index]);
}


uint8 ArgumentsParser::GetAsUInt8(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseUInt8(m_Arguments[Index]);
}


uint16 ArgumentsParser::GetAsUInt16(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseUInt16(m_Arguments[Index]);
}


uint32 ArgumentsParser::GetAsUInt32(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseUInt32(m_Arguments[Index]);
}


uint64 ArgumentsParser::GetAsUInt64(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseUInt64(m_Arguments[Index]);
}


float32 ArgumentsParser::GetAsFloat32(uint8 Index) const
{
	ASSERTION(Index < m_Arguments.GetSize(), "Index must be less than Arguments count")

		return StringConverter::ParseFloat32(m_Arguments[Index]);
}


const String &ArgumentsParser::GetAsString(const String &Parameter) const
{
	const int8 index = m_Arguments.FindIndex(Parameter);

	if (index != -1 && index + 1 < m_Arguments.GetSize())
		return m_Arguments[index + 1];

	return String::EMPTY;
}


int8 ArgumentsParser::GetAsInt8(const String &Parameter) const
{
	return StringConverter::ParseInt8(GetAsString(Parameter));
}


int16 ArgumentsParser::GetAsInt16(const String &Parameter) const
{
	return StringConverter::ParseInt16(GetAsString(Parameter));
}


int32 ArgumentsParser::GetAsInt32(const String &Parameter) const
{
	return StringConverter::ParseInt32(GetAsString(Parameter));
}


int64 ArgumentsParser::GetAsInt64(const String &Parameter) const
{
	return StringConverter::ParseInt64(GetAsString(Parameter));
}


uint8 ArgumentsParser::GetAsUInt8(const String &Parameter) const
{
	return StringConverter::ParseUInt8(GetAsString(Parameter));
}


uint16 ArgumentsParser::GetAsUInt16(const String &Parameter) const
{
	return StringConverter::ParseUInt16(GetAsString(Parameter));
}


uint32 ArgumentsParser::GetAsUInt32(const String &Parameter) const
{
	return StringConverter::ParseUInt32(GetAsString(Parameter));
}


uint64 ArgumentsParser::GetAsUInt64(const String &Parameter) const
{
	return StringConverter::ParseUInt64(GetAsString(Parameter));
}


float32 ArgumentsParser::GetAsFloat32(const String &Parameter) const
{
	return StringConverter::ParseFloat32(GetAsString(Parameter));
}


END_NAMESPACE
