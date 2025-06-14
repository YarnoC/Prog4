#pragma once
#include "Observer.h"
#include "Event.h"
#include "Component.h"

namespace dae
{
	class GameObject;
	class TextComponent;
}

class ScoreComponent final : public dae::Component, public dae::Observer
{
public:
	int GetScore() const;

	void OnNotify(const dae::Event& e, dae::Component* callerComp) override;

	ScoreComponent(dae::GameObject* owner, dae::TextComponent* textComp);

	~ScoreComponent() = default;

	ScoreComponent(const ScoreComponent&) = delete;
	ScoreComponent(ScoreComponent&&) = delete;
	ScoreComponent& operator=(const ScoreComponent&) = delete;
	ScoreComponent& operator=(ScoreComponent&&) = delete;

private:
	dae::TextComponent* m_TextComp{ nullptr };
	int m_Score{};
	bool m_IsDirty{};
};