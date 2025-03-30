#pragma once

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