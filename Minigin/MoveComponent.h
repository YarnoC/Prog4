#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
}

class MoveComponent final : public Component
{
public:
	void Update() override;
	void Move(const glm::vec2& moveVec);

	MoveComponent(dae::GameObject* owner, glm::vec2 moveVec);
	~MoveComponent() = default;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent(MoveComponent&&) = delete;
	MoveComponent& operator=(const MoveComponent&) = delete;
	MoveComponent& operator=(MoveComponent&&) = delete;

private:
	glm::vec2 m_MoveVec{};
	bool m_MoveIsDirty{ false };
};

