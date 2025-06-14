#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
}

class EnemyComponent final : public dae::Component
{
public:

	EnemyComponent(dae::GameObject* owner);

	~EnemyComponent() = default;

	EnemyComponent(const EnemyComponent&) = delete;
	EnemyComponent(EnemyComponent&&) = delete;
	EnemyComponent& operator=(const EnemyComponent&) = delete;
	EnemyComponent& operator=(EnemyComponent&&) = delete;

private:

};