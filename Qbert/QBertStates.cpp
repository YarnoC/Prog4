#include "QBertStates.h"
//#include "LevelComponent.h"
#include "QBertComponent.h"

//does nothing atm, might do something with death later
std::unique_ptr<QbertState> QIdleState::HandleState()
{
	return nullptr;
}

std::unique_ptr<QbertState> QIdleState::MoveSquare(QBertComponent* qbertComp, glm::ivec2 moveVec)
{
	auto newCoords = qbertComp->GetMapCoords() + moveVec;
	qbertComp->SetMapCoords(newCoords);
	int cubeSize{ qbertComp->GetCubeSize() };
	glm::vec3 targetPos{ cubeSize / 2 * (newCoords.x + newCoords.y), -cubeSize * 3 / 4 * (newCoords.x - newCoords.y), 0 };
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

	return nullptr;
}

QJumpingState::QJumpingState(QBertComponent* qbertComp, const glm::vec3& targetPos) :
	QbertState(qbertComp), m_TargetPos{targetPos}
{
	m_OrignalPos = qbertComp->GetOwner()->GetLocalPosition();
}

const float QJumpingState::m_JumpTime = 0.4f;