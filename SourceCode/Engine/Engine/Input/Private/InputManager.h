// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H


#include <Public\IPlugin.h>
#include <Public\Input\IInputManager.h>
#include <Public\Vector2.h>
#include <dinput.h>
#include <d3d9.h>

BEGIN_NAMESPACE

class InputManager : public IInputManager
{
public:
	InputManager(void);
	virtual ~InputManager(void);

	void Install(void);
	const String &GetName(void) const
	{
		static String name = "Input Manager";
		return name;
	}
	const String &GetVersion(void) const
	{
		static String version = "1.0.0.0";
		return version;
	}

	void Initialize(void);

	void Update(void);
	void PostUpdate(void);

	bool IsKeyDown(const KeyCodes &Code) const
	{
		return m_KeyDown[Code];
	}

	bool IsKeyPressed(const KeyCodes &Code) const
	{
		return m_KeyPressed[Code];
	}

	bool IsControlDown(void) const
	{
		return m_IsControlDown;
	}

	bool IsShiftDown(void) const
	{
		return m_IsShiftDown;
	}

	bool IsAltDown(void) const
	{
		return m_IsAltDown;
	}

	void SetCursorVisible(bool Value);
	bool IsCursorVisible(void) const
	{
		return m_isCursorVisible;
	}

	bool IsMouseHold(const MouseButtons &Button)
	{
		return m_MouseButtonHold[Button];
	}

	bool IsMouseDown(const MouseButtons &Button)
	{
		return m_MouseButtonDown[Button];
	}

	bool IsMouseClicked(const MouseButtons &Button)
	{
		return m_MouseButtonPressed[Button];
	}
	
	void SetMousePosition(int32 X, int32 Y)
	{
		SetMousePosition(Vector2((float32)X, (float32)Y));
	}
	void SetMousePosition(const Vector2 &Position);
	const Vector2 &GetMousePosition(void)
	{
		return m_MousePosition;
	}

	void SetNormalizedMousePosition(float32 X, float32 Y)
	{
		SetNormalizedMousePosition(Vector2(X, Y));
	}
	void SetNormalizedMousePosition(const Vector2 &Position);
	const Vector2 GetNormalizedMousePosition(void) const;

	void SetChar(char Character)
	{
		m_Char = Character;
	}
	char GetChar(void)
	{
		return m_Char;
	}

private:
	void InitializeKeyboard(void);
	void InitializeMouse(void);

	void CaptureKeyboard(void);
	void CaptureMouse(void);

	bool IsCursorOnWindow(void);

private:
	IDirectInput8 *m_DirectInput;

	IDirectInputDevice8 *m_Keyboard;
	uchar m_KeyBuffer[K_COUNT];
	bool m_KeyDown[K_COUNT];
	bool m_KeyPressed[K_COUNT];
	bool m_IsControlDown;
	bool m_IsShiftDown;
	bool m_IsAltDown;


	IDirectInputDevice8 *m_Mouse;
	DIMOUSESTATE2 m_MouseState;
	bool m_MouseButtonHold[M_COUNT];
	bool m_MouseButtonDown[M_COUNT];
	bool m_MouseButtonPressed[M_COUNT];
	Vector2 m_MousePosition;

	bool m_isCursorVisible;

	char m_Char;
};

END_NAMESPACE
#endif // INPUTMANAGER_H
