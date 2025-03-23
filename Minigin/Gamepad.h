#pragma once
#include "Command.h"
#include <memory>
#include "Inputs.h"

class Gamepad
{
public:
	//Command* HandleGamepadInput();
	//void RegisterCommand(const GamePadButton& button, std::unique_ptr<Command> command);
	uint8_t GetGamepadIndex() const;

	//maybe change these to take from the enum
	bool IsDownThisFrame(const GamePadButton& button) const;
	bool IsUpThisFrame(const GamePadButton& button) const;
	//currently down, not indicated when it was originally pressed
	bool IsPressed(const GamePadButton& button) const;

	Gamepad(uint8_t index);
	~Gamepad();

private:
	uint8_t m_GamepadIndex{ 0 }; //placeholder for now (?)

	class GamepadImpl;
	std::unique_ptr<GamepadImpl> m_pImpl;
};

