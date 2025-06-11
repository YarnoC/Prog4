#include "QBertStates.h"
//#include "LevelComponent.h"
#include "QBertComponent.h"
#include "GameTime.h"

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
	glm::vec2 targetPos{ cubeSize / 2 * (newCoords.x + newCoords.y), -cubeSize * 3 / 4 * (newCoords.x - newCoords.y) };
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
	//do some movement shit here, if reaches destination: return idle state (or death if out of bounds)
	constexpr float epsilon{ 25 };

	auto qObj = m_QBertComp->GetOwner();
	glm::vec2 currentPos{ qObj->GetLocalPosition().x, qObj->GetLocalPosition().y };

	const float speed{ m_Distance / m_JumpTime };
	auto moveVec{ m_TargetPos - m_OrignalPos };
	currentPos.x += moveVec.x * static_cast<float>(speed * dae::GameTime::GetDt());
	currentPos.y += moveVec.y * static_cast<float>(speed * dae::GameTime::GetDt());

	qObj->SetLocalPosition({ currentPos.x, currentPos.y, 0 });

	float sqLength{ std::powf(m_TargetPos.x - currentPos.x, 2) + std::powf(m_TargetPos.y - currentPos.y, 2) };

	if (sqLength > epsilon)
	{
		return nullptr;
	}
	
	currentPos = m_TargetPos;

	qObj->SetLocalPosition({ m_TargetPos.x, m_TargetPos.y, 0 });

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
	m_OrignalPos = { oldPos.x, oldPos.y };
	m_Distance = glm::length(targetPos - m_OrignalPos);
}

const float QJumpingState::m_JumpTime = 0.4f;