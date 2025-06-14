#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "LevelComponent.h"
#include "MultiSpriteComponent.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "ResourceManager.h"

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

	void LoadGameOverScreen(dae::Scene& workingScene, int score)
	{
		workingScene.RemoveAll();
		auto& inputMan = dae::InputManager::GetInstance();
		inputMan.UnbindAll();
		inputMan.RemoveAllGamepads();

		inputMan.AddGamepad();
		inputMan.AddGamepad();



		auto& rm = dae::ResourceManager::GetInstance();
		auto* bigFont = rm.LoadFont("Lingua.otf", 60).get();
		auto* midFont = rm.LoadFont("Lingua.otf", 40).get();
		auto* smallFont = rm.LoadFont("Lingua.otf", 30).get();

		auto* gameOverObj = workingScene.CreateGameObject();
		gameOverObj->AddComponent<dae::TextComponent>("Game Over", bigFont);

		auto* scoreObj = workingScene.CreateGameObject();
		scoreObj->AddComponent<dae::TextComponent>("Score: " + std::to_string(score), midFont);

		auto* returnObj = workingScene.CreateGameObject();
		returnObj->AddComponent<dae::TextComponent>("Press B or ESC to return to the main menu", smallFont);
	}

	//void LoadMainMenu(dae::Scene& workingScene)

}