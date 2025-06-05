#pragma once
#include "Command.h"
#include "vec2.hpp"

class MoveActorCommand final : public dae::GameActorCommand
{
public:
	MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec);
	void Execute();

private:
	glm::vec2 m_MoveVec;
};

class ToggleMuteCommand final : public dae::Command
{
public:
	ToggleMuteCommand() = default;
	void Execute();
private:
	uint8_t m_PrevEffectVol{ 128 };
	uint8_t m_PrevMusicVol{ 128 };
};