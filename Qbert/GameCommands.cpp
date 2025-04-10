#include "GameCommands.h"
#include "GameObject.h"
#include "GameTime.h"
#include <cassert>

MoveActorCommand::MoveActorCommand(dae::GameObject* actor, glm::vec2 moveVec)
    : dae::GameActorCommand(actor), m_MoveVec{ moveVec }
{
    assert(actor);
}

void MoveActorCommand::Execute()
{
    auto actor = GetGameActor();
    auto loc = actor->GetLocalPosition();
    auto dt = dae::GameTime::GetDt();
    glm::vec3 moveVec{ m_MoveVec.x * dt, m_MoveVec.y * dt, 0 };
    loc += moveVec;
    actor->SetLocalPosition(loc);
}
