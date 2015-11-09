// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\WindowUtilityAPI.h>


BEGIN_NAMESPACE


void WindowUtility_WndProc(HWND Handle, uint32 Message, WPARAM wParam, LPARAM lParam)
{
	WindowUtility::WndProc(Handle, Message, wParam, lParam);
}


END_NAMESPACE
