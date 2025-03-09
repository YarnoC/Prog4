#pragma once
#include "Xinput.h"
#include "Command.h"
#include <memory>

class GamepadHandler
{
public:
	GamepadHandler();
	Command* HandleGamepadInput();

private:
	std::unique_ptr<Command> m_MoveCommand;
};

