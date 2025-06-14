#include "QBertComponent.h"
#include "LevelComponent.h"
#include "MultiSpriteComponent.h"
#include "ServiceLocator.h"
#include "Utils.h"

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

glm::vec2 QBertComponent::CalcPlayerPos(int row, int col) const
{
	glm::vec2 cubePos = m_LevelComp->GetCubePos(row, col);
	return { cubePos.x + m_PlayerOffset.x, cubePos.y + m_PlayerOffset.y };
}

void QBertComponent::TryChangeTile()
{
	if (m_LevelCoords.x < 0 || m_LevelCoords.x > 6) return;
	if (m_LevelCoords.y < 0 || m_LevelCoords.y > m_LevelCoords.x) return;

	m_LevelComp->ChangeTile(m_LevelCoords.y, m_LevelCoords.x);
}

void QBertComponent::OnNotify(const dae::Event& event, Component*)
{
	if (event.id == dae::utils::MakeSdbmHash("LevelComplete"))
	{
		//probs do check based on gamemode
		m_LevelComp->SetupPlayer(this, LevelComponent::SpawnPos::Top);
		SetSpriteRowCol(-1, 3);
	}
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
