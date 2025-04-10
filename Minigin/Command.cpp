#include "Command.h"
#include "GameObject.h"
#include <cassert>
#include "GameTime.h"

dae::GameActorCommand::GameActorCommand(dae::GameObject* actor)
    : m_Actor{actor}
{
}

dae::GameObject* dae::GameActorCommand::GetGameActor() const
{
    return m_Actor;
}