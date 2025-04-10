#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "XInput.h"
#pragma comment(lib, "xinput.lib")

class dae::Gamepad::GamepadImpl
{
public:
	bool IsDownThisFrame(const GamepadButton& button) const;
	bool IsUpThisFrame(const GamepadButton& button) const;
	bool IsPressed(const GamepadButton& button) const;

	void Update();

	GamepadImpl(uint8_t index);

	~GamepadImpl() = default;
	GamepadImpl(const GamepadImpl&) = delete;
	GamepadImpl(GamepadImpl&&) = delete;
	GamepadImpl& operator=(const GamepadImpl&) = delete;
	GamepadImpl& operator=(GamepadImpl&&) = delete;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	DWORD m_ButtonsPressedThisFrame{};
	DWORD m_ButtonsReleasedThisFrame{};

	const uint8_t m_GamepadIndex;
};

uint8_t dae::Gamepad::GetGamepadIndex() const
{
	return m_GamepadIndex;
}

void dae::Gamepad::Update()
{
	m_pImpl->Update();
}

dae::Gamepad::Gamepad(uint8_t index)
	: m_GamepadIndex{ index },
	m_pImpl{ std::make_unique<GamepadImpl>(index) }
{

}

dae::Gamepad::~Gamepad()
{
}

bool dae::Gamepad::IsDownThisFrame(const GamepadButton& button) const
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Gamepad::IsUpThisFrame(const GamepadButton& button) const
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Gamepad::IsPressed(const GamepadButton& button) const
{
	return m_pImpl->IsPressed(button);
}

//TODO: put similar in gamepadImpl
//dae::InputManager::~InputManager()
//{
//	//needs to be defined here else the unique_ptr complains about an incomplete type
//}

//Command* dae::InputManager::GamepadHandler::HandleGamepadInput()
//{
//	//polling
//	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
//	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
//	DWORD dwResult = XInputGetState(m_GamepadIndex, &m_CurrentState);
//
//	if (dwResult != ERROR_SUCCESS) return nullptr;
//
//	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
//	m_ButtonsPressedThisFrame = buttonChanges ^ m_CurrentState.Gamepad.wButtons;
//	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
//
//	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT)) return m_LeftCmd.get();
//	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT)) return m_RightCmd.get();
//	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP)) return m_UpCmd.get();
//	if (IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN)) return m_DownCmd.get();
//
//	return nullptr;
//}

//void dae::InputManager::GamepadHandler::RegisterCommand(const GamepadButton& button, std::unique_ptr<Command> command)
//{
//	switch (button)
//	{
//	case GamepadButton::DpadLeft:
//		m_LeftCmd = std::move(command);
//		break;
//	case GamepadButton::DpadRight:
//		m_RightCmd = std::move(command);
//		break;
//	case GamepadButton::DpadUp:
//		m_UpCmd = std::move(command);
//		break;
//	case GamepadButton::DpadDown:
//		m_DownCmd = std::move(command);
//		break;
//	}
//}

//TODO: change to impl
//got pressed this frame
//bool dae::InputManager::GamepadHandler::IsDownThisFrame(unsigned int button) const
//{
//	
//}
//
////released this frame
//bool dae::InputManager::GamepadHandler::IsUpThisFrame(unsigned int button) const
//{
//	
//}
//
//bool dae::InputManager::GamepadHandler::IsPressed(unsigned int button) const
//{
//	
//}

//pressed this frame
bool dae::Gamepad::GamepadImpl::IsDownThisFrame(const GamepadButton& button) const
{
	return m_ButtonsPressedThisFrame & static_cast<DWORD>(button);
}

//released this frame
bool dae::Gamepad::GamepadImpl::IsUpThisFrame(const GamepadButton& button) const
{
	return m_ButtonsReleasedThisFrame & static_cast<DWORD>(button);
}

//currently down, not indicated when it was originally pressed
bool dae::Gamepad::GamepadImpl::IsPressed(const GamepadButton& button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<DWORD>(button);
}

void dae::Gamepad::GamepadImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_GamepadIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

dae::Gamepad::GamepadImpl::GamepadImpl(uint8_t index)
	: m_GamepadIndex{index}
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}
