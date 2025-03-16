#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include <vector>
#include "Inputs.h"
#include "Gamepad.h"

namespace dae
{
	struct GamepadCommandBind
	{
		std::unique_ptr<Command> command;
		ButtonState inputAction;
		GamePadButton button;
		uint8_t gamepadIndex;
	};

	struct KeyboardCommandBind
	{
		std::unique_ptr<Command> command;
		ButtonState inputAction;
		SDL_Scancode key;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddGamepad();
		//void RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command);

		InputManager();
		~InputManager() = default;
	private:
		const uint8_t m_MaxGamepadIndex{ 4 };
		uint8_t m_CurrentGamepadIndex{ 0 };
		std::vector<std::unique_ptr<Gamepad>> m_Gamepads;
		std::vector<std::unique_ptr<GamepadCommandBind>> m_GamepadCommands;
		std::vector<std::unique_ptr<KeyboardCommandBind>> m_KeyboardCommands;
	};

}
