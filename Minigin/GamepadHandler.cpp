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

	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT)) return m_LeftCmd.get();
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) return m_RightCmd.get();
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP)) return m_UpCmd.get();
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN)) return m_DownCmd.get();

	return nullptr;
}

void dae::InputManager::GamepadHandler::RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command)
{
	switch (button)
	{
	case GamePadButton::DpadLeft:
		m_LeftCmd = std::move(command);
		break;
	case GamePadButton::DpadRight:
		m_RightCmd = std::move(command);
		break;
	case GamePadButton::DpadUp:
		m_UpCmd = std::move(command);
		break;
	case GamePadButton::DpadDown:
		m_DownCmd = std::move(command);
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