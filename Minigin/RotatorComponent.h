#pragma once
#include "Component.h"
#include "vec3.hpp"

namespace dae
{
	class GameObject;
}

class RotatorComponent : public Component
{
public:
	void Update() override;

	//RotatorComponent(dae::GameObject* owner, const glm::vec3& axis, float radPerSec, bool turnsCw = false);
	RotatorComponent(dae::GameObject* owner, float radPerSec, bool turnsCw = false);

	~RotatorComponent() = default;
	RotatorComponent(const RotatorComponent&) = delete;
	RotatorComponent(RotatorComponent&&) = delete;
	RotatorComponent& operator=(const RotatorComponent&) = delete;
	RotatorComponent& operator=(RotatorComponent&&) = delete;

private:
	//glm::vec3 m_Axis;
	float m_RadPerSec;
	bool m_TurnsClockWise;
	float m_Radius{};
	float m_CurrentAngle{};
};

