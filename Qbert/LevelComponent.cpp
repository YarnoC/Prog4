#include "LevelComponent.h"
#include "Scene.h"
#include "CubeComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"

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

LevelComponent::LevelComponent(dae::GameObject* owner, dae::Scene* scene, int level) :
	dae::Component(owner)
{
	m_Level.resize(7);
	m_CubeSpriteSheet = dae::ResourceManager::GetInstance().LoadTexture("CubeSprite.png").get();
	const int cubeDimensions{ m_CubeSpriteSheet->GetSize().x };

	//m_CubeSpriteSheet = std::make_unique<dae::Texture2D>("CubeSprite.png");

	for (int col{}; col < 7; ++col)
	{
		m_Level[col].resize(col + 1);

		for (int i{}; i < col + 1; ++i)
		{
			auto cubeObj = std::make_unique<dae::GameObject>();
			cubeObj->SetParent(GetOwner(), false);
			glm::vec3 pos{ cubeDimensions / 2 * (col + i), -cubeDimensions * 3 / 4 * (col - i), 0 }; //if this doesn't make sense to you, i'd recommend drawing out the first 6 squares (from bottom left) and checking
			cubeObj->SetLocalPosition(pos);
			auto multiSpriteComp = cubeObj->AddComponent<dae::MultiSpriteComponent>(m_CubeSpriteSheet, 3, 1);
			auto cubeComp = cubeObj->AddComponent<CubeComponent>(multiSpriteComp, level);
			m_Level[col][i] = cubeComp;
			scene->Add(cubeObj);
		}
	}

	InitLevel(level);
}
