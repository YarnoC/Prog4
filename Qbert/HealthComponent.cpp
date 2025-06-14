#include "HealthComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "QBertComponent.h"
#include <cassert>

int HealthComponent::GetLivesCount() const
{
	return m_LivesRemaining;
}

void HealthComponent::OnNotify(const dae::Event& e, dae::Component* callerComp)
{
	if (e.id == dae::utils::MakeSdbmHash("PlayerDied"))
	{
		--m_LivesRemaining;
		if (m_LivesRemaining >= 0)
		{
			m_TextComp->SetText("Lives: " + std::to_string(m_LivesRemaining));
		}
		else
		{
			auto qbertComp = dynamic_cast<QBertComponent*>(callerComp);
			assert(qbertComp);
			qbertComp->SetDead(true);
		}
	}
}

HealthComponent::HealthComponent(dae::GameObject* owner, dae::TextComponent* textComp) :
	dae::Component(owner), m_TextComp{textComp}
{
	m_TextComp->SetText("Lives: " + std::to_string(m_LivesRemaining));
}
