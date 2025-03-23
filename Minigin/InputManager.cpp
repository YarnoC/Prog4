#pragma once
#include "InputManager.h"
#include <SDL.h>

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}

	for (auto&& gamepad : m_Gamepads)
	{
		gamepad->Update();
	}

	for (auto&& command : m_GamepadCommands)
	{
		for (auto&& gamepad : m_Gamepads)
		{
			if (gamepad->GetGamepadIndex() != command->gamepadIndex) continue;

			switch (command->inputAction)
			{
			case ButtonState::Pressed:
				if (gamepad->IsDownThisFrame(command->button))
				{
					command->command->Execute();
				}
				break;
			case ButtonState::Released:
				if (gamepad->IsUpThisFrame(command->button))
				{
					command->command->Execute();
				}
				break;
			case ButtonState::Held:
				if (gamepad->IsPressed(command->button))
				{
					command->command->Execute();
				}
				break;
			}
		}
	}

	UpdateKeyboardState();

	for (auto&& command : m_KeyboardCommands)
	{
		switch (command->inputAction)
		{
		case ButtonState::Pressed:
			if (IsKeyDownThisFrame(command->key))
			{
				command->command->Execute();
			}
			break;
		case ButtonState::Released:
			if (IsKeyUpThisFrame(command->key))
			{
				command->command->Execute();
			}
			break;
		case ButtonState::Held:
			if (IsKeyPressedThisFrame(command->key))
			{
				command->command->Execute();
			}
			break;
		}
	}

	//cmd = m_pImpl->HandleGamepadInput();

	//if (cmd)
	//{
	//	cmd->Execute();
	//}

	return true;
}

void dae::InputManager::AddGamepad()
{
	if (m_CurrentGamepadIndex >= m_MaxGamepadIndex) return;

	m_Gamepads.emplace_back(std::make_unique<Gamepad>(m_CurrentGamepadIndex));
	++m_CurrentGamepadIndex;
}

/*
void dae::InputManager::RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command)
{
	//m_pImpl->RegisterCommand(button, std::move(command));

	//switch (button)
	//{
	//case InputButton::AKey:
	//	m_LeftCmd = std::move(command);
	//	break;
	//case InputButton::DKey:
	//	m_RightCmd = std::move(command);
	//	break;
	//case InputButton::WKey:
	//	m_UpCmd = std::move(command);
	//	break;
	//case InputButton::SKey:
	//	m_DownCmd = std::move(command);
	//	break;
	//case InputButton::DpadLeft:
	//case InputButton::DpadRight:
	//case InputButton::DpadUp:
	//case InputButton::DpadDown:
	//	m_pImpl->RegisterCommand(button, std::move(command)); //allowed to waterfall cause gets sorted out in gamepadHandler.RegisterCommand()
	//	break;
	//default:
	//	break;
	//}
}
*/

dae::InputManager::InputManager()
{
	int keyAmount{};
	SDL_GetKeyboardState(&keyAmount);
	m_CurrentKeyboardState.resize(keyAmount, 0);
	m_PreviousKeyboardState.resize(keyAmount, 0);
}

bool dae::InputManager::IsKeyDownThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key] && !m_PreviousKeyboardState[key];
}

bool dae::InputManager::IsKeyUpThisFrame(SDL_Scancode key) const
{
	return !m_CurrentKeyboardState[key] && m_PreviousKeyboardState[key];
}

bool dae::InputManager::IsKeyPressedThisFrame(SDL_Scancode key) const
{
	return m_CurrentKeyboardState[key];
}

void dae::InputManager::UpdateKeyboardState()
{
	m_PreviousKeyboardState = m_CurrentKeyboardState;

	const uint8_t* state = SDL_GetKeyboardState(nullptr);
	m_CurrentKeyboardState.assign(state, state + m_CurrentKeyboardState.size());
}
