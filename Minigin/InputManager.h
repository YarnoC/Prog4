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
		void RegisterCommand(const InputButton& button, const Command& command);

		~InputManager() = default;
	private:
		class GamepadHandler;
		std::unique_ptr<GamepadHandler> m_pImpl;
		Command* m_LeftCmd{ nullptr };
		Command* m_RightCmd{ nullptr };
		Command* m_UpCmd{ nullptr };
		Command* m_DownCmd{ nullptr };
	};

}
