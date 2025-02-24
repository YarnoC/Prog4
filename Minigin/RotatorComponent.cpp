#include "RotatorComponent.h"
#include "GameObject.h"
#include <cmath>
#include "GameTime.h"

#include <iostream>

void RotatorComponent::Update()
{
	const auto& owner = GetOwner();
	m_CurrentAngle += static_cast<float>(m_RadPerSec * GameTime::GetDt());
	glm::vec3 pos{};
	int angleDirection = m_TurnsClockWise ? -1 : 1;
	pos.x = std::cos(m_CurrentAngle) * m_Radius * angleDirection;
	pos.y = std::sin(m_CurrentAngle) * m_Radius * angleDirection;
	
	//auto parent = owner->GetParent();
	
	//if (parent)
	//{
	//	m_Axis = parent->GetWorldPosition();
	//}
	
	owner->SetLocalPosition(pos);
}

//RotatorComponent::RotatorComponent(dae::GameObject* owner, const glm::vec3& axis, float radPerSec, bool turnsCw)
//	: Component(owner), m_Axis{axis}, m_RadPerSec{radPerSec}, m_TurnsClockWise{turnsCw}
//{
//	
//}

//TODO: check whether owner->GetParent() is nullptr
RotatorComponent::RotatorComponent(dae::GameObject* owner, float radPerSec, bool turnsCw)
	: Component(owner), m_RadPerSec{radPerSec}, m_TurnsClockWise{turnsCw}
{
	//m_Radius = static_cast<float>(std::abs((owner->GetWorldPosition() - m_Axis).length()));
	//glm::vec3 dist = owner->GetWorldPosition() - m_Axis;
	glm::vec3 dist = owner->GetLocalPosition();
	auto len = glm::length(dist);
	auto absLen = std::abs(len);
	m_Radius = static_cast<float>(absLen);
}
