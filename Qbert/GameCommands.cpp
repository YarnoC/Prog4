#include "GameCommands.h"
#include "GameObject.h"
#include "GameTime.h"
#include <cassert>
#include "ServiceLocator.h"

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

void ToggleMuteCommand::Execute()
{
    auto& ss = dae::ServiceLocator::GetSoundSystem();
    auto [effectVol, musicVol] = ss.GetMasterVolume();
    if (effectVol == 0)
    {
        ss.SetEffectsVolume(m_PrevEffectVol);
        ss.SetMusicVolume(m_PrevMusicVol);
        
    }
    else
    {
        ss.SetMasterVolume(0);
    }

    m_PrevEffectVol = static_cast<uint8_t>(effectVol);
    m_PrevMusicVol = static_cast<uint8_t>(musicVol);
}
