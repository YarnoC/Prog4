#include "QBertComponent.h"
#include "LevelComponent.h"

#include <iostream>

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

QBertComponent::QBertComponent(dae::GameObject* owner, LevelComponent* levelComp, dae::MultiSpriteComponent* multiSpriteComp) :
	Component(owner), m_LevelComp{levelComp}, m_SpriteComp{multiSpriteComp}, m_State{std::make_unique<QIdleState>(this)}
{
}

void QBertComponent::EnterNewState(std::unique_ptr<QbertState> newState)
{
	std::cout << "new state\n";

	m_State->OnExit(this);
	m_State = std::move(newState);
	m_State->OnEnter(this);
}
