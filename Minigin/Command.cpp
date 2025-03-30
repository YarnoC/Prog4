#include "Command.h"
#include "GameObject.h"
#include <cassert>
#include "GameTime.h"

GameActorCommand::GameActorCommand(dae::GameObject* actor)
    : m_Actor{actor}
{
}

dae::GameObject* GameActorCommand::GetGameActor() const
{
    return m_Actor;
}