// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\InputManager.h>
#include <Public\Core.h>
#include <Public\Renderer\IRenderEngine.h>
#include <WinUser.h>


BEGIN_NAMESPACE


InputManager::InputManager(void) :
	m_isCursorVisible(true)
{
}


InputManager::~InputManager(void)
{
	m_Keyboard->Unacquire();
	m_Keyboard->Release();

	m_Mouse->Unacquire();
	m_Mouse->Release();

	m_DirectInput->Release();
}
	

void InputManager::Install(void)
{
	Core::GetReference().SetInputManager(this);
}


void InputManager::Initialize(void)
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_DirectInput, NULL);

	InitializeKeyboard();
	InitializeMouse();
}


void InputManager::Update(void)
{
	CaptureKeyboard();
	CaptureMouse();
}


void InputManager::PostUpdate(void)
{
	m_Char = '\0';
}


void InputManager::SetCursorVisible(bool Value)
{
	ShowCursor(Value);

	m_isCursorVisible = Value;
}


void InputManager::SetMousePosition(const Vector2 &Position)
{
	m_MousePosition = Position;

	SetCursorPos((int32)m_MousePosition.X, (int32)m_MousePosition.Y);
}


void InputManager::SetNormalizedMousePosition(const Vector2 &Position)
{
	//SetMousePosition(Position * m_RenderWindow->GetWindowSize());
}


const Vector2 InputManager::GetNormalizedMousePosition(void) const
{
	//return m_MousePosition / m_RenderWindow->GetWindowSize();

	return Vector2::ZERO;
}


void InputManager::InitializeKeyboard(void)
{
	for (uint8 i = 0; i < K_COUNT; i++)
	{
		m_KeyBuffer[i] = '\0';
		m_KeyDown[i] = false;
		m_KeyPressed[i] = false;
	}

	m_IsAltDown = false;
	m_IsControlDown = false;
	m_IsShiftDown = false;

	m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_Keyboard, NULL);
	m_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	//m_Keyboard->SetCooperativeLevel(m_RenderWindow->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	m_Keyboard->Acquire();
}



void InputManager::InitializeMouse(void)
{
	for (uint32 i = 0; i < M_COUNT; i++)
	{
		m_MouseButtonHold[i] = false;
		m_MouseButtonDown[i] = false;
		m_MouseButtonPressed[i] = false;
	}

	m_DirectInput->CreateDevice(GUID_SysMouse, &m_Mouse, NULL);
	m_Mouse->SetDataFormat(&c_dfDIMouse2);
	//m_Mouse->SetCooperativeLevel(m_RenderWindow->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	m_Mouse->Acquire();

	DIPROPDWORD prop;
    prop.diph.dwSize = sizeof(DIPROPDWORD);
    prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    prop.diph.dwObj = 0;
    prop.diph.dwHow = DIPH_DEVICE;
	prop.dwData = 128;
	m_Mouse->SetProperty(DIPROP_BUFFERSIZE, &prop.diph);

	DIDEVCAPS MouseCapabilities;
	MouseCapabilities.dwSize = sizeof(DIDEVCAPS);
	m_Mouse->GetCapabilities(&MouseCapabilities);
	
	if (!(MouseCapabilities.dwFlags & DIDC_ATTACHED))
		LOG_WARNING("IInputManager initialized without any mouse, because there's no connected device")
}


void InputManager::CaptureKeyboard(void)
{
	if (!IsCursorOnWindow())
		return;

	HRESULT result = m_Keyboard->GetDeviceState(sizeof(m_KeyBuffer), m_KeyBuffer);

	if (FAILED(result))
	{
		// It's possible that we lost access to the keyboard
		// Here we acquire access to the keyboard again
		m_Keyboard->Acquire();
	}

	//m_IsControlDown = (GetKeyState(VK_CONTROL) < 0);
	m_IsControlDown = ((GetKeyState(VK_CONTROL) & 0x8000) != 0);
	//m_IsShiftDown = (GetKeyState(VK_SHIFT) < 0);
	m_IsShiftDown = ((GetKeyState(VK_SHIFT) & 0x8000) != 0);
	m_IsAltDown = (GetKeyState(VK_MENU) < 0);

	for (uint8 i = 0; i < K_COUNT; i++)
	{
		bool isDown = (m_KeyBuffer[i] != 0);

		if (m_KeyDown[i])
		{
			if (!isDown)
			{
				m_KeyDown[i] = false;
				m_KeyPressed[i] = true;
			}
		}
		else
			m_KeyPressed[i] = false;

		m_KeyDown[i] = isDown;
	}
}


void InputManager::CaptureMouse(void)
{
	if (IsCursorOnWindow())
	{
		m_Mouse->Acquire();
		m_Mouse->GetDeviceState(sizeof(m_MouseState), &m_MouseState);

		for (uint32 i = 0; i < M_COUNT; i++)
		{
			const bool isHold = (m_MouseState.rgbButtons[i] & 0x80) != 0;

			if (m_MouseButtonHold[i])
			{
				m_MouseButtonDown[i] = false;

				if (!isHold)
				{
					m_MouseButtonHold[i] = false;
					m_MouseButtonPressed[i] = true;
				}
			}
			else
			{
				if (isHold)
					m_MouseButtonDown[i] = true;

				m_MouseButtonPressed[i] = false;
			}

			m_MouseButtonHold[i] = isHold;

		}
	}

	POINT point;
	GetCursorPos(&point);
	//ScreenToClient(m_RenderWindow->GetHandle(), &point);

	m_MousePosition.X = (float32)point.x;
	m_MousePosition.Y = (float32)point.y;

	//const Vector2 &size = m_RenderWindow->GetWindowSize();
		
	//if (m_MousePosition.X < 0)
	//	m_MousePosition.X = 0;
	//else if (m_MousePosition.X > size.X)
	//	m_MousePosition.X = size.X;

	//if (m_MousePosition.Y < 0)
	//	m_MousePosition.Y = 0;
	//else if (m_MousePosition.Y > size.Y)
	//	m_MousePosition.Y = size.Y;
}


bool InputManager::IsCursorOnWindow(void)
{
	POINT point;
	GetCursorPos(&point);

	//return (WindowFromPoint(point) == m_RenderWindow->GetHandle());

	return false;
}

END_NAMESPACE
