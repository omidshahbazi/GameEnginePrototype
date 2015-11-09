// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef UTILITIES_H
#define UTILITIES_H
#include <Public\Common.h>
#include <wtypes.h>

BEGIN_NAMESPACE

class Utilities
{
public:
	static String FromWideCharString(BSTR Value);
	static BSTR ToWideCharString(const String &Value);
};

#define TO_String(BSTR) Utilities::FromWideCharString(BSTR)
#define TO_BSTR(String) Utilities::ToWideCharString(String)

#define API_FUNCTION EXTERN_C CWRAPPER_API

END_NAMESPACE
#endif // UTILITIES_H
