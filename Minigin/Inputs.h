#pragma once
#include "SDL_events.h"
#include "SDL_scancode.h"

enum class GamePadButton
{
	DpadUp = 0x0001,
	DpadDown = 0x0002,
	DpadLeft = 0x0004,
	DpadRight = 0x0008,
	Start = 0x0010,
	Settings = 0x0020,
	L3 = 0x0040,
	R3 = 0x0080,
	BumperLeft = 0x0100,
	BumperRight = 0x0200,
	AButton = 0x1000,
	BButton = 0x2000,
	XButton = 0x4000,
	YButton = 0x8000
};

enum class ButtonState
{
	Pressed,
	Released,
	Held
};