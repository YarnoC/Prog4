#include "QBertStates.h"

//does nothing atm, might do something with death later
std::unique_ptr<QbertState> QIdleState::HandleState()
{
	return nullptr;
}

std::unique_ptr<QbertState> QIdleState::MoveSquare(glm::ivec2 /*moveVec*/)
{
	
	return std::unique_ptr<QbertState>();
}

QIdleState::QIdleState() :
	QbertState()
{
}
