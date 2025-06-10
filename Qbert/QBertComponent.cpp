#include "QBertComponent.h"
#include "LevelComponent.h"

void QBertComponent::Move(glm::ivec2 moveVec)
{
	auto newState = m_State->MoveSquare(this, moveVec);

	if (newState == nullptr) return;

	m_State->OnExit(this);
	m_State = std::move(newState);
	m_State->OnEnter(this);
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
