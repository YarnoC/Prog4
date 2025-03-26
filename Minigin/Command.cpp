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

MoveActorCommand::MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec)
    : GameActorCommand(actor), m_MoveVec{moveVec}
{
    assert(actor); //maybe change
}

void MoveActorCommand::Execute()
{
    auto actor = GetGameActor();
    auto loc = actor->GetLocalPosition();
    auto dt = GameTime::GetDt();
    glm::vec3 moveVec{ m_MoveVec.x * dt, m_MoveVec.y, 0 };
    loc += moveVec;
    actor->SetLocalPosition(loc);
}
