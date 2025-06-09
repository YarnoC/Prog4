#include "CubeComponent.h"

void CubeComponent::OnLandOn()
{
	const int threshold{ m_Level + 1 };
	switch (m_Level)
	{
	case 0:
	case 1:
	{
		if (m_Stage < threshold)
		{
			++m_Stage;
		}
		break;
	}
	case 2:
	{
		m_Stage = m_Stage + 1 % threshold;
		break;
	}
	}
}

void CubeComponent::SetToLevel(int level)
{
	m_Level = level;
	m_Stage = 0;
}

CubeComponent::CubeComponent(dae::GameObject* owner, dae::MultiSpriteComponent* spriteComp, int level) :
	dae::Component(owner), m_Sprite{spriteComp}, m_Level{level}
{
}
