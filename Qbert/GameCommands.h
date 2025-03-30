#pragma once
#include "Command.h"
#include "vec2.hpp"

class MoveActorCommand final : public GameActorCommand
{
public:
	MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec);
	void Execute();

private:
	glm::vec2 m_MoveVec;
};