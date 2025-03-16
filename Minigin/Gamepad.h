#pragma once
#include "Command.h"
#include <memory>

class Gamepad
{
public:
	//Command* HandleGamepadInput();
	//void RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command);
	uint8_t GetGamepadIndex() const;

	Gamepad(uint8_t index);
	~Gamepad();

private:
	uint8_t m_GamepadIndex{ 0 }; //placeholder for now (?)

	class GamepadImpl;
	std::unique_ptr<GamepadImpl> m_pImpl;

	//maybe change these to take from the enum
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
};

