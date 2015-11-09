// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef NATIVEWINDOW_H
#define NATIVEWINDOW_H

#include <Public\WindowUtility.h>

BEGIN_NAMESPACE

class CORE_API NativeWindow : public WindowUtility::IListener
{
public:
	NativeWindow(WindowUtility::WindowHandle Handle);
	NativeWindow(const String &Text);
	virtual ~NativeWindow(void);

protected:
	virtual void OnSizeChanged(const Vector2 &Size);

	virtual void OnLostFocus(void)
	{
		m_HasFocus = false;
	}
	virtual void OnGetFocus(void)
	{
		m_HasFocus = true;
	}
	virtual void OnClose(void)
	{
		Close();
	}

public:
	virtual WindowUtility::WindowHandle GetHandle(void) const
	{
		return m_Handle;
	}

	virtual void SetText(const String &Text);

	virtual void Show(void);
	virtual void Close(void);

	virtual const Vector2 &GetPosition(void) const
	{
		return m_Position;
	}
	virtual void SetPosition(const Vector2 &Size);

	virtual const Vector2 &GetSize(void) const
	{
		return m_Size;
	}
	virtual const Vector2 GetActualSize(void) const
	{
		return m_ActualSize;
	}
	virtual void SetSize(const Vector2 &Size);

	virtual bool GetFullScreen(void)
	{
		return m_FullScreen;
	}
	virtual void SetFullScreen(void);

	virtual bool HasFocus(void) const
	{
		return m_HasFocus;
	}
	
protected:
	virtual void UpdateSizeChanges(void);

protected:
	WindowUtility::WindowHandle m_Handle;
	bool m_ExternalWindow;
	Vector2 m_Position;
	Vector2 m_Size;
	Vector2 m_ActualSize;
	bool m_FullScreen;
	bool m_HasFocus;
	bool m_Hidden;
};

END_NAMESPACE
#endif // NATIVEWINDOW_H
