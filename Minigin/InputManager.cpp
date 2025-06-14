#pragma once
#include "InputManager.h"
#include <SDL.h>
#include <cassert>

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
		if (m_IsDirty) break;

		for (auto&& gamepad : m_Gamepads)
		{
			if (m_IsDirty) break;

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
		if (m_IsDirty) break;

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

	m_IsDirty = false;

	return true;
}

void dae::InputManager::AddGamepad()
{
	if (m_CurrentGamepadIndex >= m_MaxGamepadIndex) return;

	m_Gamepads.emplace_back(std::make_unique<Gamepad>(m_CurrentGamepadIndex));
	++m_CurrentGamepadIndex;
	m_IsDirty = true;
}

void dae::InputManager::RemoveGamepad(uint8_t gamepadIndex)
{
	assert(gamepadIndex < m_CurrentGamepadIndex);
	//remove gamepad from list
	std::erase_if(m_Gamepads, [gamepadIndex](std::unique_ptr<Gamepad>& gamepad) { return gamepad->GetGamepadIndex() == gamepadIndex; });
	//remove all commands associated with the removed controllers
	std::erase_if(m_GamepadCommands, [gamepadIndex](std::unique_ptr<GamepadCommandBind>& command) { return command->gamepadIndex == gamepadIndex; });
	--m_CurrentGamepadIndex;
	m_IsDirty = true;
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> command, GamepadButton gamepadButton, ButtonState inputAction, uint8_t gamepadIndex)
{
	assert(gamepadIndex < m_CurrentGamepadIndex); //current idx starts at 0 and after add gamepad becomes 1 so the passed index must always be lower than current
	auto commandUPtr = std::make_unique<GamepadCommandBind>(std::move(command), inputAction, gamepadButton, gamepadIndex);
	m_GamepadCommands.emplace_back(std::move(commandUPtr));
}

void dae::InputManager::BindCommand(std::unique_ptr<Command> command, SDL_Scancode key, ButtonState inputAction)
{
	auto commandUPtr = std::make_unique<KeyboardCommandBind>(std::move(command), inputAction, key);
	m_KeyboardCommands.emplace_back(std::move(commandUPtr));
	m_IsDirty = true;
}

void dae::InputManager::UnbindCommand(GamepadButton gamepadButton, uint8_t gamepadIndex)
{
	std::erase_if(m_GamepadCommands, [&](std::unique_ptr<GamepadCommandBind>& command) { return command->gamepadIndex == gamepadIndex && command->button == gamepadButton; });
	m_IsDirty = true;
}

void dae::InputManager::UnbindCommand(SDL_Scancode key)
{
	std::erase_if(m_KeyboardCommands, [&](std::unique_ptr<KeyboardCommandBind>& command) { return command->key == key; });
	m_IsDirty = true;
}

void dae::InputManager::UnbindAll()
{
	m_GamepadCommands.clear();
	m_KeyboardCommands.clear();
	m_IsDirty = true;
}

void dae::InputManager::RemoveAllGamepads()
{
	m_Gamepads.clear();
	m_CurrentGamepadIndex = 0;
	m_IsDirty = true;
}

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
