#include "LevelComponent.h"
#include "Scene.h"
#include "CubeComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "QBertComponent.h"

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

//void LevelComponent::SetupPlayer(QBertComponent* qbert, SpawnPos spawnPos)
//{
//	auto qObj = qbert->GetOwner();
//	qObj->SetLocalPosition({ m_PlayerCubeOffset.x, m_PlayerCubeOffset.y, 0 });
//
//	switch (spawnPos)
//	{
//	case SpawnPos::BottomLeft:
//	{
//		auto parent = m_Level[0][0]->GetOwner();
//		qObj->SetParent(parent, false);
//		break;
//	}
//	case SpawnPos::Top:
//	{
//		auto parent = m_Level[0].back()->GetOwner();
//		qObj->SetParent(parent, false);
//		break;
//	}
//	case SpawnPos::BottomRight:
//	{
//		auto parent = m_Level.back().back()->GetOwner();
//		qObj->SetParent(parent, false);
//		break;
//	}
//	}
//}

//void LevelComponent::Move(QBertComponent* qbertComp, glm::ivec2 moveVec)
//{
//	auto newPos = qbertComp->GetMapCoords() + moveVec;
//
//	if (newPos.x < 0 || newPos.x > 6) return;
//	if (newPos.y < 0 || newPos.y > 6) return;
//}

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

	InitLevel(level);
}
