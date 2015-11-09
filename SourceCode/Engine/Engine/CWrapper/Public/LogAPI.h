// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LOGAPI_H
#define LOGAPI_H
#include <Public\Log.h>
#include <Public\Utilities.h>


BEGIN_NAMESPACE

typedef void(__stdcall *LogCallback)(const char*, int);

API_FUNCTION void Log_SetCallback(LogCallback Callback);

END_NAMESPACE
#endif // LOGAPI_H
