#pragma once
#include "Singleton.h"
#include <memory>
#include "Command.h"
#include <vector>
#include "Inputs.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command);

		InputManager();
		~InputManager();
	private:
		class GamepadHandler;
		std::unique_ptr<GamepadHandler> m_pImpl;
	};

}
