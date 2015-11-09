// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifdef _DEBUG

#include <Public\Exception.h>
#include <Public\Log.h>
#include <Public\Enum.h>
#include <exception>

BEGIN_NAMESPACE

DEFINE_SINGLETON(Exception)

void Exception::Throw(const ExceptionReasons &Reason, const String &Text, const String &Detail, bool StopProcess)
{
	static const EnumType *const type = Enum::GetType("ExceptionReasons");

	LOG_ERROR_DEBUG(String("(") + Enum::ToString(type, (int32)Reason) + ") " + Text + (Detail.GetLength() ? " {" + Detail + "}" : ""))

	//if (StopProcess)
	//	exit(-1);
		//throw("WTF in Exception::Throw");
}

END_NAMESPACE

#endif
