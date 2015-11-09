// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <Public\Common.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Colour.h>


BEGIN_NAMESPACE

class BASIC_API StringConverter
{
public:
	static String ToString(float32 Value, uint16 Precision = 6, uint16 Width = 0, const char Fill = ' ', std::ios::fmtflags Flags = std::ios::fmtflags(0));

	static String ToString(int32 Value, uint16 Width = 0, const char Fill = ' ', std::ios::fmtflags Flags = std::ios::fmtflags(0));

	static String ToString(const uint32 Value, uint16 Width = 0, const char Fill = ' ', std::ios::fmtflags Flags = std::ios::fmtflags(0));

	static String ToString(const uint64 &Value, uint16 Width = 0, const char Fill = ' ', std::ios::fmtflags Flags = std::ios::fmtflags(0));

	static String ToString(const int64 &Value, uint16 Width = 0, const char Fill = ' ', std::ios::fmtflags Flags = std::ios::fmtflags(0));

	static String ToString(bool Value, bool YesNo = false);

	static String ToString(const Colour &Value);

	static String ToString(const Vector2 &Value);

	static String ToString(const Vector3 &Value);

	//static String ToString(const StringVector& Value);

	static float32 ParseFloat32(const String &Value, float32 DefaultValue = 0.f);

	static int8 ParseInt8(const String &Value, int8 DefaultValue = 0);
	static int16 ParseInt16(const String &Value, int16 DefaultValue = 0);
	static int32 ParseInt32(const String &Value, int32 DefaultValue = 0);
	static int64 ParseInt64(const String &Value, const int64 &DefaultValue = 0);

	static uint8 ParseUInt8(const String &Value, uint8 DefaultValue = 0);
	static uint16 ParseUInt16(const String &Value, uint16 DefaultValue = 0);
	static uint32 ParseUInt32(const String &Value, uint32 DefaultValue = 0);
	static uint64 ParseUInt64(const String &Value, const uint64 &DefaultValue = 0);

	static bool ParseBool(const String &Value, bool DefaultValue = false);

	static Vector2 ParseVector2(const String &Value, const Vector2 &DefaultValue = Vector2::ZERO);

	static Vector3 ParseVector3(const String &Value, const Vector3 &DefaultValue = Vector3::ZERO);

	static Colour ParseColour(const String &Value, const Colour &DefaultValue = Colour::WHITE);

	//static StringList ParseStringVector(const String &Value);

	static bool IsNumber(const String &Value);
};


END_NAMESPACE
#endif // STRINGCONVERTER_H
