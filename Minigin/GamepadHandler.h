#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "XInput.h"
#pragma comment(lib, "xinput.lib")

#include "Command.h"
#include <memory>
#include "InputManager.h"

class dae::InputManager::GamepadHandler
{
public:
	Command* HandleGamepadInput();
	void RegisterCommand(const InputButton& button, std::unique_ptr<Command> command);

	GamepadHandler();
	~GamepadHandler();

private:
	std::unique_ptr<Command> m_MoveCommand;
	uint8_t m_GamepadIndex{ 0 }; //placeholder for now (?)

	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};

	std::unique_ptr<Command> m_LeftCmd{ nullptr };
	std::unique_ptr<Command> m_RightCmd{ nullptr };
	std::unique_ptr<Command> m_UpCmd{ nullptr };
	std::unique_ptr<Command> m_DownCmd{ nullptr };

	std::vector <std::unique_ptr<Command>> m_Commands;

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
};

