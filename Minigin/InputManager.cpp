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
}
