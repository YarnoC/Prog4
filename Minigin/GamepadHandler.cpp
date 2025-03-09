#include "GamepadHandler.h"

dae::InputManager::GamepadHandler::GamepadHandler()
{

}

dae::InputManager::GamepadHandler::~GamepadHandler()
{
}

dae::InputManager::~InputManager()
{
	//needs to be defined here else the unique_ptr complains about an incomplete type
}

Command* dae::InputManager::GamepadHandler::HandleGamepadInput()
{
	//polling
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_GamepadIndex, &m_CurrentState);

	if (dwResult != ERROR_SUCCESS) return nullptr;

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges ^ m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT)) return m_LeftCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) return m_RightCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP)) return m_UpCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN)) return m_DownCmd;

	return nullptr;
}

void dae::InputManager::GamepadHandler::RegisterCommand(const InputButton& button, Command* command)
{
	switch (button)
	{
	case InputButton::DpadLeft:
		m_LeftCmd = command;
		break;
	case InputButton::DpadRight:
		m_RightCmd = command;
		break;
	case InputButton::DpadUp:
		m_UpCmd = command;
		break;
	case InputButton::DpadDown:
		m_DownCmd = command;
		break;
	}
}

//got pressed this frame
bool dae::InputManager::GamepadHandler::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

//released this frame
bool dae::InputManager::GamepadHandler::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

//is down this frame, either already or pressed this frame
bool dae::InputManager::GamepadHandler::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons ^ button;
}