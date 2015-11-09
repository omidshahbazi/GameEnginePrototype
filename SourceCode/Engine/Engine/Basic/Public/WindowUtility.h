// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef WINDOWUTILITY_H
#define WINDOWUTILITY_H

#include <Public\Common.h>
#include <Public\Vector2.h>
#include <Public\ListenerHolder.h>
#include <Windows.h>

BEGIN_NAMESPACE

static class BASIC_API WindowUtility
{
public:
	typedef HWND WindowHandle;

	BEGIN_DECLARE_STATIC_LISTENER_HOLDER
		virtual void OnSizeChanged(const Vector2 &Size) = 0;
		virtual void OnLostFocus(void) = 0;
		virtual void OnGetFocus(void) = 0;
		virtual void OnClose(void) = 0;
		
		virtual WindowHandle GetHandle(void) const = 0;
	END_DECLARE_STATIC_LISTENER_HOLDER

public:
	static void PumpMessages(void);

	static LRESULT __stdcall WndProc(WindowHandle Handle, uint32 Message, WPARAM wParam, LPARAM lParam);

private:
	typedef Vector<IListener*> IListenersList;
} WindowUtility_Dummy;

END_NAMESPACE
#endif // WINDOWUTILITY_H
