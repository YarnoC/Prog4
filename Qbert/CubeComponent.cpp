#include "CubeComponent.h"

bool CubeComponent::NextCubeColor(bool endOfLevel)
{
	int threshold{ m_Level + 1 };

	if (endOfLevel)
	{
		threshold = 3;
		m_Stage = (m_Stage + 1) % threshold;
		m_Sprite->SetToRowCollumn(m_Stage, -1);
		return false;
	}

	switch (m_Level)
	{
	case 0:
	case 1:
	{
		if (m_Stage < threshold)
		{
			++m_Stage;
			m_Sprite->NextRow();
			return true;
		}
		break;
	}
	case 2:
	{
		threshold = 2;
		m_Stage = (m_Stage + 1) % threshold;
		m_Sprite->SetToRowCollumn(m_Stage, -1);
		return true;
		break;
	}
	}

	return false;
}

void CubeComponent::PrevCubeColor()
{
	m_Stage = std::max(0, m_Stage - 1);
}

void CubeComponent::SetToLevel(int level)
{
	m_Level = level;
	m_Stage = 0;
	m_Sprite->SetToRowCollumn(m_Stage, -1);
}

bool CubeComponent::IsInCorrectState() const
{
	if (m_Level == 2) return m_Stage == 1;

	return m_Stage == m_Level + 1;
}

CubeComponent::CubeComponent(dae::GameObject* owner, dae::MultiSpriteComponent* spriteComp, int level) :
	dae::Component(owner), m_Sprite{spriteComp}, m_Level{level}
{
}
