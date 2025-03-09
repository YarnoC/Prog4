#include <SDL.h>
#include "GamepadHandler.h"

bool dae::InputManager::ProcessInput()
{
	Command* cmd{ nullptr };

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.scancode)
			{
			case SDL_SCANCODE_LEFT:
				cmd = m_LeftCmd;
				break;
			case SDL_SCANCODE_RIGHT:
				cmd = m_RightCmd;
				break;
			case SDL_SCANCODE_UP:
				cmd = m_UpCmd;
				break;
			case SDL_SCANCODE_DOWN:
				cmd = m_DownCmd;
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	cmd = m_pImpl->HandleGamepadInput();

	if (cmd)
	{
		cmd->Execute();
	}

	return true;
}

dae::InputManager::InputManager()
	: m_pImpl{ std::make_unique<GamepadHandler>() }
{
}
