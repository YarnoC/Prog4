#include "MoveComponent.h"
#include "GameTime.h"
#include "GameObject.h"

void MoveComponent::Update()
{
	if (m_MoveIsDirty)
	{
		auto owner = GetOwner();
		auto pos = owner->GetLocalPosition();
		auto dt = GameTime::GetDt();
		glm::vec3 newPos{ pos.x + m_MoveVec.x * dt, pos.y + m_MoveVec.y * dt, 0 };
		owner->SetLocalPosition(newPos);
		m_MoveIsDirty = false;
	}
}

void MoveComponent::Move(const glm::vec2& moveVec)
{
	m_MoveVec = moveVec;
	m_MoveIsDirty = true;
}

MoveComponent::MoveComponent(dae::GameObject* owner)
	: Component(owner), m_MoveVec{}
{
}
