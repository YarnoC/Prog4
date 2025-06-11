#include "QBertStates.h"
//#include "LevelComponent.h"
#include "QBertComponent.h"
#include "GameTime.h"

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
	int cubeSize{ qbertComp->GetCubeSize() };
	glm::vec2 targetPos{ cubeSize / 2 * (newCoords.x + newCoords.y) + qbertComp->GetPlayerOffset().x, -cubeSize * 3 / 4 * (newCoords.x - newCoords.y) + qbertComp->GetPlayerOffset().y };
	return std::make_unique<QJumpingState>(qbertComp, targetPos);
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

	auto moveVec{ m_TargetPos - m_OriginalPos };
	const float moveTime{ 0.2f };
	const float xSpeed{ xDif / moveTime };
	const float ySpeed{ yDif / moveTime };
	//currentPos.x += moveVec.x * static_cast<float>(speed * dae::GameTime::GetDt());
	//currentPos.y += moveVec.y * static_cast<float>(speed * dae::GameTime::GetDt());

	currentPos.x += xSpeed * static_cast<float>(dae::GameTime::GetDt());
	currentPos.y += ySpeed * static_cast<float>(dae::GameTime::GetDt());

	qObj->SetLocalPosition({ currentPos.x, currentPos.y, 0 });

	float sqDistRemaining{ std::powf(m_TargetPos.x - currentPos.x, 2) + std::powf(m_TargetPos.y - currentPos.y, 2) };

	std::cout << sqDistRemaining << std::endl;

	if (sqDistRemaining > epsilon)
	{
		return nullptr;
	}
	
	currentPos = m_TargetPos;

	qObj->SetLocalPosition({ currentPos.x, currentPos.y, 0 });

	auto coords = m_QBertComp->GetMapCoords();
	if (coords.x < 0 || coords.x > 6 || coords.y < 0 || coords.y > 6)
	{
		//return death state
	}

	return std::make_unique<QIdleState>(m_QBertComp);
}

QJumpingState::QJumpingState(QBertComponent* qbertComp, const glm::vec2& targetPos) :
	QbertState(qbertComp), m_TargetPos{targetPos}
{
	auto oldPos = qbertComp->GetOwner()->GetLocalPosition();
	m_OriginalPos = { oldPos.x, oldPos.y };
	//m_Distance = glm::length(targetPos - m_OriginalPos);
	//m_Distance = 64;
}

const float QJumpingState::m_JumpTime = 0.4f;