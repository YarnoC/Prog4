#include "ScoreComponent.h"
#include <sstream>
#include "GameObject.h"
#include "TextComponent.h"

int ScoreComponent::GetScore() const
{
	return m_Score;
}

void ScoreComponent::OnNotify(const dae::Event& e, dae::Component*)
{
	if (e.id == dae::utils::MakeSdbmHash("ChangedTileColor"))
	{
		m_Score += 25;
		m_TextComp->SetText("Score: " + std::to_string(m_Score));
	}
}

ScoreComponent::ScoreComponent(dae::GameObject* owner, dae::TextComponent* textComp) :
	Component(owner), m_TextComp{textComp}
{
	m_TextComp->SetText("Score: " + m_Score);
}
