#include "GamepadHandler.h"

GamepadHandler::GamepadHandler()
{

}

Command* GamepadHandler::HandleGamepadInput()
{
	//polling
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_GamepadIndex, &m_CurrentState);

	if (dwResult != ERROR_SUCCESS) return;

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges ^ m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT)) return m_LeftCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) return m_RightCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP)) return m_UpCmd;
	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN)) return m_DownCmd;

	return nullptr;
}

//got pressed this frame
bool GamepadHandler::IsDownThisFrame(unsigned int button) const
{
	return m_ButtonsPressedThisFrame & button;
}

//released this frame
bool GamepadHandler::IsUpThisFrame(unsigned int button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

//is down this frame, either already or pressed this frame
bool GamepadHandler::IsPressed(unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons ^ button;
}