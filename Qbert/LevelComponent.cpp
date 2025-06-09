#include "LevelComponent.h"
#include "Scene.h"
#include "CubeComponent.h"
#include "GameObject.h"

void LevelComponent::InitLevel(int level)
{
	for (auto&& collumn : m_Level)
	{
		for (auto&& cube : collumn)
		{
			cube->SetToLevel(level);
		}
	}

	//move the discs around based on the file stuff
}

LevelComponent::LevelComponent(dae::GameObject* owner, dae::Scene& /*scene*/, int level) :
	dae::Component(owner)
{
	m_Level.reserve(7);
	for (int col{}; col < 7; ++col)
	{
		m_Level[col].reserve(col + 1);

		for (int i{}; i < col + 1; ++i)
		{
			auto cubeObj = std::make_unique<dae::GameObject>();
		}
	}

	InitLevel(level);
}
