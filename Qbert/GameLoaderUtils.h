#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "LevelComponent.h"
#include "MultiSpriteComponent.h"S

namespace glu
{
	void LoadLevel(dae::Scene& scene)
	{
		auto levelObj = std::make_unique<dae::GameObject>();
		auto levelComp = levelObj->AddComponent<LevelComponent>(&scene, 0);
		levelObj->SetLocalPosition({ 96, 450, 0 });
		scene.Add(levelObj);
	}

	void LoadSinglePlayer()
	{
		//auto& levelScene = dae::SceneManager::GetInstance().CreateScene("singlePlayer");

		//auto qbertObj = std::make_unique<dae::GameObject>();
		//auto spriteComp = qbertObj->AddComponent<dae::MultiSpriteComponent>("QBertSpritesheet.png", 1, 4);
		//auto qbertComp = qbertObj->AddComponent<QBertComponent>(levelComp, spriteComp);
		//levelComp->SetupPlayer(qbertComp, LevelComponent::SpawnPos::Top);
	}
}