#include "Command.h"
#include "MoveComponent.h"
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
    assert(actor);

    m_MoveComponent = actor->GetComponent<MoveComponent>();
}

void MoveActorCommand::Execute()
{
    auto actor = GetGameActor();
    auto loc = actor->GetLocalPosition();
    loc += m_MoveVec;
    auto dt = GameTime::GetDt();
    actor->SetLocalPosition({ loc.x * dt, loc.y * dt, 0 });
    //m_MoveComponent->Move(m_MoveVec);
}
