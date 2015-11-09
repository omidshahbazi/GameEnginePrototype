// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\NativeWindow.h>


BEGIN_NAMESPACE


const String WINDOW_CLASS_NAME = "IERenderWindow";


NativeWindow::NativeWindow(WindowUtility::WindowHandle Handle) :
m_Handle(Handle),
m_ExternalWindow(true),
m_FullScreen(false),
m_Hidden(false)
{
	RECT rect;
	GetWindowRect(Handle, &rect);

	m_Size.X = float32(rect.right - rect.left);
	m_Size.Y = float32(rect.bottom - rect.top);

	WindowUtility::AddListener(this);
}


NativeWindow::NativeWindow(const String &Text) :
m_Handle(NULL),
m_ExternalWindow(false),
m_FullScreen(false),
m_Hidden(true)
{
	static bool classRegistered = false;

	if (!classRegistered)
	{
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowUtility::WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(0);
		wc.hIcon = LoadIcon(0, IDI_APPLICATION);
		wc.hCursor = LoadCursor(0, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		wc.lpszMenuName = 0;
		wc.lpszClassName = WINDOW_CLASS_NAME.GetBuffer();

		if (RegisterClass(&wc))
			classRegistered = true;
	}

	m_Handle = CreateWindow(WINDOW_CLASS_NAME.GetBuffer(), Text.GetBuffer(), WS_CLIPCHILDREN, 1, 1, 100, 100, NULL, NULL, GetModuleHandle(0), NULL);

	if (!m_Handle)
		THROW_EXCEPTION_AND_STOP(Exception::ER_UNKNOWN, "Creating window failed", "RenderWindow::Initialize")

		SetSize(Vector2::ONE);

	WindowUtility::AddListener(this);
}


NativeWindow::~NativeWindow(void)
{
	WindowUtility::RemoveListener(this);

	if (m_ExternalWindow)
		return;

	Close();
	DestroyWindow(m_Handle);
}


void NativeWindow::OnSizeChanged(const Vector2 &Size)
{
	m_Size = Size;
}


void NativeWindow::SetText(const String &Text)
{
	if (m_ExternalWindow)
		return;

	SetWindowText(m_Handle, Text.GetBuffer());
}


void NativeWindow::Show(void)
{
	if (m_ExternalWindow || !m_Hidden)
		return;

	ShowWindow(m_Handle, SW_SHOW);
	UpdateWindow(m_Handle);
}


void NativeWindow::Close(void)
{
	if (m_ExternalWindow || m_Hidden)
		return;

	ShowWindow(m_Handle, SW_HIDE);
	UpdateWindow(m_Handle);
}


void NativeWindow::SetPosition(const Vector2 &Position)
{
	if (m_ExternalWindow || m_FullScreen)
		return;

	if (m_Position == Position)
		return;

	if (Position < Vector2::ZERO)
		m_Position = Vector2::ZERO;
	else
		m_Position = Position;

	SetWindowPos(m_Handle, NULL, (int32)m_Position.X, (int32)m_Position.Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}


void NativeWindow::SetSize(const Vector2 &Size)
{
	if (m_ExternalWindow)
		return;

	if (Size == Vector2::ZERO || m_Size == Size)
		return;

	m_FullScreen = false;
	m_Size = Size;

	UpdateSizeChanges();
}


void NativeWindow::SetFullScreen(void)
{
	if (m_ExternalWindow)
		return;

	m_FullScreen = true;

	m_Size.X = (float32)GetSystemMetrics(SM_CXSCREEN);
	m_Size.Y = (float32)GetSystemMetrics(SM_CYSCREEN);

	UpdateSizeChanges();
}


void NativeWindow::UpdateSizeChanges(void)
{
	if (m_ExternalWindow)
		return;

	uint32 windowStyle = WS_VISIBLE | WS_CLIPCHILDREN;

	if (m_FullScreen)
		windowStyle |= WS_POPUP;
	else
		windowStyle |= WS_OVERLAPPEDWINDOW;
	//style |= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	SetWindowLong(m_Handle, GWL_STYLE, windowStyle);

	uint32 swpflags = SWP_NOACTIVATE | SWP_NOMOVE;

	if (m_Hidden)
		swpflags |= SWP_HIDEWINDOW;

	if (m_FullScreen)
	{
		swpflags |= SWP_NOSIZE | SWP_NOZORDER;
		SetWindowPos(m_Handle, HWND_TOPMOST, 0, 0, 0, 0, swpflags);

		m_ActualSize = m_Size;
	}
	else
	{
		swpflags |= SWP_DRAWFRAME | SWP_FRAMECHANGED;
		SetWindowPos(m_Handle, HWND_NOTOPMOST, 0, 0, (int32)m_Size.X, (int32)m_Size.Y, swpflags);

		SetPosition(Vector2((GetSystemMetrics(SM_CXSCREEN) - m_Size.X) / 2.0F, (GetSystemMetrics(SM_CYSCREEN) - m_Size.Y) / 2.0F));

		RECT rect;
		SetRect(&rect, 0, 0, (int32)m_Size.X, (int32)m_Size.Y);
		AdjustWindowRect(&rect, windowStyle, false);

		m_ActualSize.X = float32(rect.right - rect.left);
		m_ActualSize.Y = float32(rect.bottom - rect.top);
	}
}

END_NAMESPACE
