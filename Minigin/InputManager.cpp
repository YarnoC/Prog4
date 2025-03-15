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
				cmd = m_LeftCmd.get();
				break;
			case SDL_SCANCODE_RIGHT:
				cmd = m_RightCmd.get();
				break;
			case SDL_SCANCODE_UP:
				cmd = m_UpCmd.get();
				break;
			case SDL_SCANCODE_DOWN:
				cmd = m_DownCmd.get();
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

void dae::InputManager::RegisterCommand(const InputButton& button, std::unique_ptr<Command> command)
{
	m_pImpl->RegisterCommand(button, std::move(command));

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

dae::InputManager::InputManager()
	: m_pImpl{ std::make_unique<GamepadHandler>() }
{
}
