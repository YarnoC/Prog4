#include "GameCommands.h"
#include "GameObject.h"
#include "GameTime.h"
#include <cassert>
#include "ServiceLocator.h"
#include "QBertComponent.h"
#include "LevelComponent.h"
#include "GameStateComponent.h"

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

MoveQBertCommand::MoveQBertCommand(QBertComponent* qbertComp, glm::ivec2 moveVec) :
    m_QBertComp{qbertComp}, m_MoveVec{moveVec}
{
}

void MoveQBertCommand::Execute()
{
    m_QBertComp->Move(m_MoveVec);
}

SkipLevelCommand::SkipLevelCommand(LevelComponent* levelComp, QBertComponent* qbertComp, QBertComponent* qbertCompP2) :
    Command(), m_LevelComp{levelComp}, m_QBertComp{qbertComp}, m_QBertComp2{qbertCompP2}
{
}

void SkipLevelCommand::Execute()
{
    auto newLevel = m_LevelComp->GetCurrentLevel() + 1;
    m_LevelComp->SetCurrentLevel(newLevel);
    m_LevelComp->InitLevel(newLevel);

    if (!m_QBertComp2)
    {
        m_LevelComp->SetupPlayer(m_QBertComp, LevelComponent::SpawnPos::Top);
    }
    else
    {
        m_LevelComp->SetupPlayer(m_QBertComp, LevelComponent::SpawnPos::BottomLeft);
        m_LevelComp->SetupPlayer(m_QBertComp2, LevelComponent::SpawnPos::BottomRight);
    }
}

ReturnToMenuCmd::ReturnToMenuCmd(GameStateComponent* gameStateComp) :
    dae::Command(), m_GameStateComp{gameStateComp}
{
}

void ReturnToMenuCmd::Execute()
{
    //a bit of a hack but i'm not making a subject for this
    m_GameStateComp->OnNotify(dae::Event{ dae::utils::MakeSdbmHash("ToMainMenu") }, m_GameStateComp);
}

SelectMenuCmd::SelectMenuCmd(GameStateComponent* gameStateComp, dae::GameObject* obj, bool reverse) :
    dae::Command(), m_GameStateComp{ gameStateComp }, m_Obj{ obj }, m_Reverse{ reverse }
{
}

void SelectMenuCmd::Execute()
{
    m_GameStateComp->NextMenuOption(m_Reverse);
    m_GameStateComp->UpdateCursorPos(m_Obj);
}

ConfirmChoice::ConfirmChoice(GameStateComponent* gameStateComp) :
    dae::Command(), m_GameStateComp{gameStateComp}
{
}

void ConfirmChoice::Execute()
{
    m_GameStateComp->OnNotify(dae::Event{ dae::utils::MakeSdbmHash("MenuConfirm") }, m_GameStateComp);
}
