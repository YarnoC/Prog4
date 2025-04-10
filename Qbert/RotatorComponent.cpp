#include "RotatorComponent.h"
#include "GameObject.h"
#include <cmath>
#include "GameTime.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

const float RotatorComponent::m_2Pi = static_cast<float>(M_PI * 2);

void RotatorComponent::Update()
{
	const auto& owner = GetOwner();
	m_CurrentAngle += static_cast<float>(m_RadPerSec * dae::GameTime::GetDt());
	if (m_CurrentAngle > m_2Pi)
	{
		m_CurrentAngle -= m_2Pi;
	}
	glm::vec3 pos{};
	int angleDirection = m_TurnsClockWise ? -1 : 1;
	pos.x = std::cos(m_CurrentAngle) * m_Radius * angleDirection;
	pos.y = std::sin(m_CurrentAngle) * m_Radius * angleDirection;
	
	owner->SetLocalPosition(pos);
}

RotatorComponent::RotatorComponent(dae::GameObject* owner, float radPerSec, bool turnsCw)
	: Component(owner), m_RadPerSec{radPerSec}, m_TurnsClockWise{turnsCw}
{
	glm::vec3 dist = owner->GetLocalPosition();
	auto len = glm::length(dist);
	auto absLen = std::abs(len);
	m_Radius = static_cast<float>(absLen);
}
