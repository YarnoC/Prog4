#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "XInput.h"
#pragma comment(lib, "xinput.lib")

#include "Command.h"
#include <memory>

class GamepadHandler
{
public:
	GamepadHandler();
	Command* HandleGamepadInput();

private:
	std::unique_ptr<Command> m_MoveCommand;
	uint8_t m_GamepadIndex{ 0 }; //placeholder for now (?)

	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};

	Command* m_LeftCmd{ nullptr };
	Command* m_RightCmd{ nullptr };
	Command* m_UpCmd{ nullptr };
	Command* m_DownCmd{ nullptr };

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
};

