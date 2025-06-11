#include "QBertComponent.h"
#include "LevelComponent.h"
#include "MultiSpriteComponent.h"
#include "ServiceLocator.h"

void QBertComponent::Move(glm::ivec2 moveVec)
{
	auto newState = m_State->MoveSquare(this, moveVec);

	if (newState == nullptr) return;

	EnterNewState(std::move(newState));
}

glm::ivec2 QBertComponent::GetMapCoords() const
{
	return m_LevelCoords;
}

void QBertComponent::SetMapCoords(glm::ivec2 newCoords)
{
	m_LevelCoords = newCoords;
}

int QBertComponent::GetCubeSize() const
{
	return m_LevelComp->GetCubeSize();
}

glm::ivec2 QBertComponent::GetPlayerOffset() const
{
	return m_PlayerOffset;
}

void QBertComponent::SetSpriteRowCol(int row, int col)
{
	m_SpriteComp->SetToRowCollumn(row, col);
}

const QBertComponent::Sounds& QBertComponent::GetQBertSounds() const
{
	return m_Sounds;
}

void QBertComponent::Update()
{
	auto newState = m_State->Update();
	if (newState != nullptr)
	{
		EnterNewState(std::move(newState));
	}
}

QBertComponent::QBertComponent(dae::GameObject* owner, LevelComponent* levelComp, dae::MultiSpriteComponent* multiSpriteComp) :
	Component(owner), m_LevelComp{levelComp}, m_SpriteComp{multiSpriteComp}, m_State{std::make_unique<QIdleState>(this)}
{
	auto& ss = dae::ServiceLocator::GetSoundSystem();
	m_Sounds.jump = ss.LoadEffect("Sounds/QBertJump.ogg");
	m_Sounds.fall = ss.LoadEffect("Sounds/QBertFall.ogg");
	m_Sounds.curse = ss.LoadEffect("Sounds/QBertCurse.ogg");
	SetSpriteRowCol(-1, 3);
}

void QBertComponent::EnterNewState(std::unique_ptr<QbertState> newState)
{
	m_State->OnExit();
	m_State = std::move(newState);
	m_State->OnEnter();
}
