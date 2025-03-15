#pragma once
#include "glm.hpp"

namespace dae
{
	class GameObject;
}

class Command
{
public:
	virtual ~Command(){}
	virtual void Execute() = 0;
};

class GameActorCommand : public Command
{
public:
	GameActorCommand(dae::GameObject* actor);

protected:
	dae::GameObject* GetGameActor() const;

private:
	dae::GameObject* m_Actor;
};

class MoveActorCommand final : public GameActorCommand
{
public:
	MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec);
	void Execute();

private:
	glm::vec2 m_MoveVec;
};

