// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\WindowUtility.h>
#include <Windows.h>
//#include "Public/Input/IInputManager.h"

BEGIN_NAMESPACE


DEFINE_STATIC_LISTENER_HOLDER(WindowUtility)


void WindowUtility::PumpMessages(void)
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		//if (msg.message == WM_QUIT)
		//	return true;

		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}


LRESULT __stdcall WindowUtility::WndProc(WindowHandle Handle, uint32 Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CHAR:
	{
					//Core::GetReference().GetInputManager()->SetChar(wParam);
	} return 0;

	case WM_SIZE:
	//case WM_MOVE:
	{
					FOR_EACH(listener, m_Listeners)
					if (listener->GetHandle() == Handle)
					{
						RECT rect;
						GetWindowRect(Handle, &rect);

						listener->OnSizeChanged(Vector2(float32(rect.right - rect.left), float32(rect.bottom - rect.top)));

						break;
					}
	} return 0;

	//case WM_ACTIVATE:
	//	{
	//		FOR_EACH(listener, m_Listeners)
	//			if (listener->GetHandle() == Handle)
	//			{
	//				if (LOWORD(wParam) == WA_INACTIVE)
	//					listener->OnLostFocus();
	//				else
	//					listener->OnGetFocus();
	//			}
	//	} return 0;

	case WM_DESTROY:
	{
					   FOR_EACH(listener, m_Listeners)
					   if (listener->GetHandle() == Handle)
					   {
						   listener->OnClose();

						   break;
					   }
	} return 0;
	}

	return DefWindowProc(Handle, Message, wParam, lParam);
}


END_NAMESPACE
