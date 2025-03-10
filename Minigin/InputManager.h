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
		void RegisterCommand(const InputButton& button, std::unique_ptr<Command> command);

		InputManager();
		~InputManager();
	private:
		class GamepadHandler;
		//GamepadHandler* m_pImpl;
		std::unique_ptr<GamepadHandler> m_pImpl;
		std::unique_ptr<Command> m_LeftCmd{ nullptr };
		std::unique_ptr<Command> m_RightCmd{ nullptr };
		std::unique_ptr<Command> m_UpCmd{ nullptr };
		std::unique_ptr<Command> m_DownCmd{ nullptr };
	};

}
