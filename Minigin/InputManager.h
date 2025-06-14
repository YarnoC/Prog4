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
		GamepadButton button;
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
		void RemoveGamepad(uint8_t gamepadIndex);
		void BindCommand(std::unique_ptr<Command> command, GamepadButton gamepadButton, ButtonState inputAction, uint8_t gamepadIndex);
		void BindCommand(std::unique_ptr<Command> command, SDL_Scancode key, ButtonState inputAction);
		void UnbindCommand(GamepadButton gamepadButton, uint8_t gamepadIndex);
		void UnbindCommand(SDL_Scancode key);
		void UnbindAll();
		void RemoveAllGamepads();

		InputManager();
		~InputManager() = default;
	private:
		const uint8_t m_MaxGamepadIndex{ 4 };
		uint8_t m_CurrentGamepadIndex{ 0 };
		std::vector<std::unique_ptr<Gamepad>> m_Gamepads;
		std::vector<std::unique_ptr<GamepadCommandBind>> m_GamepadCommands;
		std::vector<std::unique_ptr<KeyboardCommandBind>> m_KeyboardCommands;

		std::vector<uint8_t> m_CurrentKeyboardState;
		std::vector<uint8_t> m_PreviousKeyboardState;

		bool IsKeyDownThisFrame(SDL_Scancode key) const;
		bool IsKeyUpThisFrame(SDL_Scancode key) const;
		bool IsKeyPressedThisFrame(SDL_Scancode key) const;

		void UpdateKeyboardState();
	};

}
