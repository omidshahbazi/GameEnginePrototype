// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Utilities.h>
#include <comutil.h>

BEGIN_NAMESPACE


String Utilities::FromWideCharString(BSTR Value)
{
	std::wstring wstr(Value);

	if (!wstr.length())
		return "";

	char *str = new char[wstr.length() + 1];

	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length() + 1, str, wstr.length() + 1, 0, 0);

	return str;
}


BSTR Utilities::ToWideCharString(const String &Value)
{
	uint32 len = Value.GetLength() + 1;

	uint32 nlen = MultiByteToWideChar(CP_ACP, 0, Value.GetBuffer(), len, 0, 0) - 1;

	std::wstring ret(nlen, '\0');

	MultiByteToWideChar(CP_ACP, 0, Value.GetBuffer(), len, &ret[0], nlen);

	return ::SysAllocString(ret.c_str());
}


END_NAMESPACE
