#include "CubeComponent.h"

void dae::CubeComponent::NextStage()
{
	++m_Stage;
}

dae::CubeComponent::CubeComponent(dae::GameObject* owner, dae::MultiSpriteComponent* spriteComp, int level) :
	Component(owner), m_Sprite{spriteComp}, m_Level{level}
{
}
