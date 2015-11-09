// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\StringConverter.h>
#include <Public\StringUtility.h>
#include <sstream>

using namespace std;


BEGIN_NAMESPACE


String StringConverter::ToString(float32 Value, uint16 Precision, uint16 Width, char Fill, std::ios::fmtflags Flags)
{
	stringstream stream;
	stream.precision(Precision);
	stream.width(Width);
	stream.fill(Fill);
	if (Flags)
		stream.setf(Flags);
	stream << Value;
	return String(stream.str().c_str());
}


String StringConverter::ToString(int32 Value, uint16 Width, char Fill, std::ios::fmtflags Flags)
{
	stringstream stream;
	stream.width(Width);
	stream.fill(Fill);
	if (Flags)
		stream.setf(Flags);
	stream << Value;
	return String(stream.str().c_str());
}


String StringConverter::ToString(const uint32 Value, uint16 Width, char Fill, std::ios::fmtflags Flags)
{
	stringstream stream;
	stream.width(Width);
	stream.fill(Fill);
	if (Flags)
		stream.setf(Flags);
	stream << Value;
	return String(stream.str().c_str());
}


String StringConverter::ToString(const uint64 &Value, uint16 Width, char Fill, std::ios::fmtflags Flags)
{
	stringstream stream;
	stream.width(Width);
	stream.fill(Fill);
	if (Flags)
		stream.setf(Flags);
	stream << Value;
	return String(stream.str().c_str());
}


String StringConverter::ToString(const int64 &Value, uint16 Width, char Fill, std::ios::fmtflags Flags)
{
	stringstream stream;
	stream.width(Width);
	stream.fill(Fill);
	if (Flags)
		stream.setf(Flags);
	stream << Value;
	return String(stream.str().c_str());
}


String StringConverter::ToString(bool Value, bool YesNo)
{
	if (Value)
	{
		if (YesNo)
			return "Yes";
		else
			return "True";
	}
	else
	{
		if (YesNo)
			return "No";
		else
			return "False";
	}
}


String StringConverter::ToString(const Colour &Value)
{
	stringstream stream;
	stream << Value.GetRed() << " " << Value.GetGreen() << " " << Value.GetBlue() << " " << Value.GetAlpha();
	return String(stream.str().c_str());
}


String StringConverter::ToString(const Vector2 &Value)
{
	stringstream stream;
	stream << Value.X << " " << Value.Y;
	return String(stream.str().c_str());
}


String StringConverter::ToString(const Vector3 &Value)
{
	stringstream stream;
	stream << Value.X << " " << Value.Y << " " << Value.Z;
	return String(stream.str().c_str());
}


float32 StringConverter::ParseFloat32(const String &Value, float32 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	float32 ret = DefaultValue;
	str >> ret;

	return ret;
}


int8 StringConverter::ParseInt8(const String &Value, int8 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	int16 ret = DefaultValue;
	str >> ret;

	return (int8)ret;
}


int16 StringConverter::ParseInt16(const String &Value, int16 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	int16 ret = DefaultValue;
	str >> ret;

	return ret;
}


int32 StringConverter::ParseInt32(const String &Value, int32 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	int32 ret = DefaultValue;
	str >> ret;

	return ret;
}


int64 StringConverter::ParseInt64(const String &Value, const int64 &DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	int64 ret = DefaultValue;
	str >> ret;

	return ret;
}


uint8 StringConverter::ParseUInt8(const String &Value, uint8 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	uint16 ret = DefaultValue;
	str >> ret;

	return (uint8)ret;
}


uint16 StringConverter::ParseUInt16(const String &Value, uint16 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	uint16 ret = DefaultValue;
	str >> ret;

	return ret;
}


uint32 StringConverter::ParseUInt32(const String &Value, uint32 DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	uint32 ret = DefaultValue;
	str >> ret;

	return ret;
}


uint64 StringConverter::ParseUInt64(const String &Value, const uint64 &DefaultValue)
{
	stringstream str(Value.TrimAll().GetBuffer());
	uint64 ret = DefaultValue;
	str >> ret;

	return ret;
}


bool StringConverter::ParseBool(const String &Value, bool DefaultValue)
{
	if ((Value.StartsWith("True") || Value.StartsWith("Yes") || Value.StartsWith("1")))
		return true;
	else if ((Value.StartsWith("False") || Value.StartsWith("No") || Value.StartsWith("0")))
		return false;
	else
		return DefaultValue;
}


Vector2 StringConverter::ParseVector2(const String &Value, const Vector2 &DefaultValue)
{
	StringsList vec = Value.Split(",");

	if (vec.GetSize() != 2)
		return DefaultValue;
	else
		return Vector2(ParseFloat32(vec[0]), ParseFloat32(vec[1]));
}


Vector3 StringConverter::ParseVector3(const String &Value, const Vector3 &DefaultValue)
{
	StringsList vec = Value.Split(",");

	if (vec.GetSize() != 3)
		return DefaultValue;
	else
		return Vector3(ParseFloat32(vec[0]), ParseFloat32(vec[1]), ParseFloat32(vec[2]));
}


Colour StringConverter::ParseColour(const String &Value, const Colour &DefaultValue)
{
	StringsList vec = Value.Split(",");

	if (vec.GetSize() == 3)
		return Colour(ParseUInt8(vec[0]), ParseUInt8(vec[1]), ParseUInt8(vec[2]));
	else if (vec.GetSize() == 4)
		return Colour(ParseUInt8(vec[0]), ParseUInt8(vec[1]), ParseUInt8(vec[2]), ParseUInt8(vec[3]));
	else
		return DefaultValue;
}


//StringList StringConverter::ParseStringVector(const String &Value)
//{
//return StringUtil::split(val);
//}


bool StringConverter::IsNumber(const String &Value)
{
	stringstream str(Value.GetBuffer());
	float32 tst;
	str >> tst;
	return !str.fail() && str.eof();
}


END_NAMESPACE
