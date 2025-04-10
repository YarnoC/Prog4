#pragma once
#include "Command.h"
#include <memory>
#include "Inputs.h"

namespace dae
{

class Gamepad
{
public:
	uint8_t GetGamepadIndex() const;
	void Update();

	bool IsDownThisFrame(const GamepadButton& button) const;
	bool IsUpThisFrame(const GamepadButton& button) const;
	//currently down, not indicated when it was originally pressed
	bool IsPressed(const GamepadButton& button) const;

	Gamepad(uint8_t index);
	~Gamepad();

private:
	uint8_t m_GamepadIndex{ 0 };

	class GamepadImpl;
	std::unique_ptr<GamepadImpl> m_pImpl;
};

}
