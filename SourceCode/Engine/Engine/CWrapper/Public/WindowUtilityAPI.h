// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef WINDOWUTILITYAPI_H
#define WINDOWUTILITYAPI_H
#include <Public\WindowUtility.h>
#include <Public\Utilities.h>


BEGIN_NAMESPACE

API_FUNCTION void WindowUtility_WndProc(HWND Handle, uint32 Message, WPARAM wParam, LPARAM lParam);

END_NAMESPACE
#endif // WINDOWUTILITYAPI_H
