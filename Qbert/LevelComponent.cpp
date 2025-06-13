#include "LevelComponent.h"
#include "Scene.h"
#include "CubeComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "QBertComponent.h"
#include "LevelStates.h"

void LevelComponent::Update()
{
	auto newState = m_LevelState->Update();
	if (newState != nullptr)
	{
		m_LevelState = std::move(newState);
		m_LevelState->OnEnter();
	}
}

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

int LevelComponent::GetCubeSize() const
{
	return m_CubeSize;
}

void LevelComponent::ChangeTile(int row, int col, bool forward)
{
	if (forward)
	{
		m_Level[col][row]->NextCubeColor();
		
		auto newState = m_LevelState->CheckTiles(m_Level);
		if (newState)
		{
			m_LevelState = std::move(newState);
		}

		return;
	}

	m_Level[col][row]->PrevCubeColor();


}

int LevelComponent::GetCurrentLevel() const
{
	return m_LevelNumber;
}

void LevelComponent::SetCurrentLevel(int newLevel)
{
	m_LevelNumber = newLevel;
}

void LevelComponent::SetupPlayer(QBertComponent* qbertComp, SpawnPos spawnPos)
{
	auto levelObj = GetOwner();
	auto qbertObj = qbertComp->GetOwner();
	qbertObj->SetParent(levelObj, false);

	glm::vec3 offset{ m_PlayerCubeOffset.x, m_PlayerCubeOffset.y, 0 };

	switch (spawnPos)
	{
	case SpawnPos::BottomLeft:
	{
		qbertComp->SetMapCoords({ 0, 0 });

		//qbertObj->SetLocalPosition(offset);
		break;
	}
	case SpawnPos::Top:
	{
		qbertComp->SetMapCoords({ 6, 0 });

		//glm::vec3 pos{ m_CubeSize / 2 * (col + row), -m_CubeSize * 3 / 4 * (col - row), 0 }; //reference formula
		//glm::vec3 pos{ m_CubeSize / 2 * 7, -m_CubeSize * 3 / 4 * 7, 0 };
		//qbertObj->SetLocalPosition(pos + offset);
		break;
	}
	case SpawnPos::BottomRight:
	{
		qbertComp->SetMapCoords({ 6, 6 });


		//glm::vec3 pos{ m_CubeSize / 2 * 7, -m_CubeSize * 3 / 4 * 7, 0 };
		//qbertObj->SetLocalPosition(pos + offset);
		break;
	}
	}

	glm::ivec2 coords{ qbertComp->GetMapCoords() };

	//glm::vec3 pos{ m_CubeSize / 2 * (coords.x + coords.y), -m_CubeSize * 3 / 4 * (coords.x - coords.y), 0};
	glm::vec3 pos{ GetCubePos(coords.y, coords.x).x, GetCubePos(coords.y, coords.x).y, 0 };

	qbertObj->SetLocalPosition(pos + offset);
}

glm::vec2 LevelComponent::GetCubePos(int row, int col) const
{
	return glm::vec2{ m_CubeSize / 2 * (col + row), -m_CubeSize * 3 / 4 * (col - row) };
}

LevelComponent::LevelComponent(dae::GameObject* owner, dae::Scene* scene, int level) :
	dae::Component(owner)
{
	m_Level.resize(7);
	m_CubeSpriteSheet = dae::ResourceManager::GetInstance().LoadTexture("CubeSprite.png").get();
	m_CubeSize = m_CubeSpriteSheet->GetSize().x;
	
	for (int col{}; col < 7; ++col)
	{
		m_Level[col].resize(col + 1);

		for (int i{}; i < col + 1; ++i)
		{
			auto cubeObj = std::make_unique<dae::GameObject>();
			cubeObj->SetParent(GetOwner(), false);
			glm::vec3 pos{ m_CubeSize / 2 * (col + i), -m_CubeSize * 3 / 4 * (col - i), 0 };
			cubeObj->SetLocalPosition(pos);
			auto multiSpriteComp = cubeObj->AddComponent<dae::MultiSpriteComponent>(m_CubeSpriteSheet, 3, 1);
			auto cubeComp = cubeObj->AddComponent<CubeComponent>(multiSpriteComp, level);
			m_Level[col][i] = cubeComp;
			scene->Add(cubeObj);
		}
	}

	m_LevelState = std::make_unique<LevelPlayingState>(this);

	InitLevel(level);
}

LevelComponent::~LevelComponent() = default;
