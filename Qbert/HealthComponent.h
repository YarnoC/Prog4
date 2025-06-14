#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class TextComponent;
}

class HealthComponent final : public dae::Component, public dae::Observer
{
public:
	int GetLivesCount() const;

	void OnNotify(const dae::Event& e, dae::Component* callerComp) override;

	HealthComponent(dae::GameObject* owner, dae::TextComponent* textComp);

	~HealthComponent() = default;

	HealthComponent(const HealthComponent&) = delete;
	HealthComponent(HealthComponent&&) = delete;
	HealthComponent& operator=(const HealthComponent&) = delete;
	HealthComponent& operator=(HealthComponent&&) = delete;

private:
	dae::TextComponent* m_TextComp{ nullptr };
	const int m_TotalLives{ 3 };
	int m_LivesRemaining{ m_TotalLives };
};