#include "QBertStates.h"
//#include "LevelComponent.h"
#include "QBertComponent.h"
#include "GameTime.h"
#include "ServiceLocator.h"
#include <algorithm>

#include <iostream>

//does nothing atm, might do something with death later
//std::unique_ptr<QbertState> QIdleState::HandleState()
//{
//	return nullptr;
//}

std::unique_ptr<QbertState> QIdleState::MoveSquare(QBertComponent* qbertComp, glm::ivec2 moveVec)
{
	auto newCoords = qbertComp->GetMapCoords() + moveVec;
	qbertComp->SetMapCoords(newCoords);
	return std::make_unique<QJumpingState>(qbertComp, m_QBertComp->CalcPlayerPos(newCoords.y, newCoords.x));
}

QIdleState::QIdleState(QBertComponent* qbertComp) :
	QbertState(qbertComp)
{
}

QbertState::QbertState(QBertComponent* qbertComp) :
	m_QBertComp{qbertComp}
{
}


std::unique_ptr<QbertState> QJumpingState::Update()
{
	constexpr float epsilon{ 25 };

	auto qObj = m_QBertComp->GetOwner();
	glm::vec2 currentPos{ qObj->GetLocalPosition().x, qObj->GetLocalPosition().y };

	int xDif{ static_cast<int>(m_TargetPos.x - m_OriginalPos.x) };
	int yDif{ static_cast<int>(m_TargetPos.y - m_OriginalPos.y) };

	bool left = xDif < 0 ? true : false;
	bool down = yDif > 0 ? true : false;

	int col = left + down * 2;
	m_QBertComp->SetSpriteRowCol(0, col);

	const float moveTime{ 0.2f };
	const float xSpeed{ xDif / moveTime };
	const float ySpeed{ yDif / moveTime };

	currentPos.x += xSpeed * static_cast<float>(dae::GameTime::GetDt());
	currentPos.y += ySpeed * static_cast<float>(dae::GameTime::GetDt());

	qObj->SetLocalPosition({ currentPos.x, currentPos.y, 0 });

	float sqDistRemaining{ std::powf(m_TargetPos.x - currentPos.x, 2) + std::powf(m_TargetPos.y - currentPos.y, 2) };

	if (sqDistRemaining > epsilon)
	{
		return nullptr;
	}
	
	currentPos = m_TargetPos;

	qObj->SetLocalPosition({ currentPos.x, currentPos.y, 0 });

	auto coords = m_QBertComp->GetMapCoords();
	if (coords.x < 0 || coords.x > 6 || coords.y < 0 || coords.y > 6)
	{
		m_SoundToPlay = m_QBertComp->GetQBertSounds().fall;
		return std::make_unique<QDeadState>(m_QBertComp);
	}

	m_SoundToPlay = m_QBertComp->GetQBertSounds().jump;
	return std::make_unique<QIdleState>(m_QBertComp);
}

void QJumpingState::OnExit()
{
	dae::ServiceLocator::GetSoundSystem().Play(m_SoundToPlay, 32, false);
}

QJumpingState::QJumpingState(QBertComponent* qbertComp, const glm::vec2& targetPos) :
	QbertState(qbertComp), m_TargetPos{targetPos}
{
	auto oldPos = qbertComp->GetOwner()->GetLocalPosition();
	m_OriginalPos = { oldPos.x, oldPos.y };
}

const float QJumpingState::m_JumpTime = 0.4f;

QDeadState::QDeadState(QBertComponent* qbertComp) :
	QbertState(qbertComp)
{
}

void QDeadState::OnEnter()
{
	dae::ServiceLocator::GetSoundSystem().Play(m_QBertComp->GetQBertSounds().curse, 32, false);
}

std::unique_ptr<QbertState> QDeadState::Update()
{
	m_DeadTimer -= dae::GameTime::GetDt();

	if (m_DeadTimer < 0)
	{
		glm::ivec2 coords = m_QBertComp->GetMapCoords();
		coords.x = std::clamp(coords.x, 0, 6);
		coords.y = std::clamp(coords.y, 0, 6);
		m_QBertComp->SetMapCoords(coords);

		auto newPos = m_QBertComp->CalcPlayerPos(coords.y, coords.x);
		m_QBertComp->GetOwner()->SetLocalPosition(glm::vec3{ newPos.x, newPos.y, 0 });

		return std::make_unique<QIdleState>(m_QBertComp);
	}

	return std::unique_ptr<QbertState>();
}
