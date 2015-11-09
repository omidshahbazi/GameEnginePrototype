// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IRENDERWINDOW_H
#define IRENDERWINDOW_H

#include <Public\NativeWindow.h>

BEGIN_NAMESPACE

class ICamera;

class IRenderWindow : public NativeWindow
{
public:
	IRenderWindow(WindowUtility::WindowHandle Handle) :
		NativeWindow(Handle)
	{
	}
	IRenderWindow(const String &Text) :
		NativeWindow(Text)
	{
	}
	virtual ~IRenderWindow(void) {}

	virtual ICamera *GetCamera(void) const = 0;
	virtual void SetCamera(ICamera *Camera) = 0;
};

END_NAMESPACE
#endif // IRENDERWINDOW_H
