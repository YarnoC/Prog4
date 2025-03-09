#pragma once
#include "Singleton.h"
#include <memory>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		~InputManager() = default;
	private:
		class InputHandler;
		std::unique_ptr<InputHandler> m_pImpl;
	};

}
