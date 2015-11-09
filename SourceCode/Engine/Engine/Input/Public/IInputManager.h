// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IINPUTMANAGER_H
#define IINPUTMANAGER_H

#include <Public\IPlugin.h>
#include <Public\KeyCodes.h>

BEGIN_NAMESPACE

struct Vector2;

//<Description>
//This is sample description
class IInputManager : public IPlugin
{
public:
	enum class MouseButtons
	{
		M_LEFT = 0,
		M_RIGHT,
		M_MIDDLE,
		M_BUTTON3,
		M_BUTTON4,
		M_BUTTON5,
		M_BUTTON6,
		M_BUTTON7,
		M_COUNT
	};		

public:
	virtual ~IInputManager(void) {}

	virtual void Initialize(void) = 0;

	virtual void Update(void) = 0;
	virtual void PostUpdate(void) = 0;

	//virtual bool IsModifierDown(const Modifier &Modifier) = 0;

	virtual bool IsKeyDown(const KeyCodes &Code) const = 0;
	virtual bool IsKeyPressed(const KeyCodes &Code) const = 0;
	virtual bool IsControlDown(void) const = 0;
	virtual bool IsShiftDown(void) const = 0;
	virtual bool IsAltDown(void) const = 0;

	virtual void SetCursorVisible(bool Value) = 0;
	virtual bool IsCursorVisible(void) const = 0;

	virtual bool IsMouseHold(const MouseButtons &Button) = 0;
	virtual bool IsMouseDown(const MouseButtons &Button) = 0;
	virtual bool IsMouseClicked(const MouseButtons &Button) = 0;

	virtual void SetMousePosition(int32 X, int32 Y) = 0;
	virtual void SetMousePosition(const Vector2 &Position) = 0;
	virtual const Vector2 &GetMousePosition(void) = 0;
	virtual void SetNormalizedMousePosition(float32 X, float32 Y) = 0;
	virtual void SetNormalizedMousePosition(const Vector2 &Position) = 0;
	virtual const Vector2 GetNormalizedMousePosition(void) const = 0;

	virtual void SetChar(char Character) = 0;
	virtual char GetChar(void) = 0;
};

END_NAMESPACE
#endif // IINPUTMANAGER_H
