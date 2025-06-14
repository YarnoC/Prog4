#include "GameStateComponent.h"
#include "Scene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameCommands.h"
#include "Inputs.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "MultiSpriteComponent.h"
#include "LevelComponent.h"
#include "Observer.h"
#include "QBertComponent.h"

#include <iostream>

GameStateComponent::GameMode GameStateComponent::m_GameMode = GameStateComponent::GameMode::Solo;

void GameStateComponent::OnNotify(const dae::Event& e, dae::Component*)
{
	if (e.id == dae::utils::MakeSdbmHash("OutOfLives"))
	{
		LoadGameOverScreen();
	}
	else if (e.id == dae::utils::MakeSdbmHash("ToMainMenu"))
	{
		LoadMainMenu();
	}
	else if (e.id == dae::utils::MakeSdbmHash("MenuConfirm"))
	{
		switch (m_MenuChoice)
		{
		case 0:
			LoadSinglePlayer();
			std::cout << "sp\n";
			break;
		case 1:
			//load coop
			std::cout << "coop\n";
			break;
		case 2:
			//load versus
			std::cout << "versue\n";
			break;
		}
	}
}

const GameStateComponent::GameMode& GameStateComponent::GetGameMode()
{
	return m_GameMode;
}

void GameStateComponent::NextMenuOption(bool reverse)
{
	if (reverse)
	{
		m_MenuChoice = (3 + m_MenuChoice - 1) % 3;
	}
	else
	{
		m_MenuChoice = (m_MenuChoice + 1) % 3;
	}
}

void GameStateComponent::UpdateCursorPos(dae::GameObject* obj)
{
	glm::vec3 pos{ 240, 0, 0 };
	switch (m_MenuChoice)
	{
	case 0:
		pos.y = 200;
		break;
	case 1:
		pos.y = 280;
		break;
	case 2:
		pos.y = 360;
		break;
	}

	obj->SetLocalPosition(pos);
}

GameStateComponent::GameStateComponent(dae::GameObject* owner) :
	dae::Component(owner)
{
	m_WorkingScene = &dae::SceneManager::GetInstance().CreateScene("workScene");
	LoadMainMenu();
}

void GameStateComponent::LoadGameOverScreen()
{
	m_WorkingScene->RemoveAll();
	auto& inputMan = dae::InputManager::GetInstance();
	inputMan.UnbindAll();
	inputMan.RemoveAllGamepads();

	inputMan.AddGamepad();
	inputMan.AddGamepad();

	//bind the return buttons here
	auto returnCmdG1 = std::make_unique<ReturnToMenuCmd>(this);
	auto returnCmdG2 = std::make_unique<ReturnToMenuCmd>(this);
	auto returnCmdKb = std::make_unique<ReturnToMenuCmd>(this);
	inputMan.BindCommand(std::move(returnCmdG1), GamepadButton::BButton, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(returnCmdG2), GamepadButton::BButton, ButtonState::Pressed, 1);
	inputMan.BindCommand(std::move(returnCmdKb), SDL_SCANCODE_ESCAPE, ButtonState::Pressed);

	auto& rm = dae::ResourceManager::GetInstance();
	auto* bigFont = rm.LoadFont("Lingua.otf", 60).get();
	auto* midFont = rm.LoadFont("Lingua.otf", 40).get();
	auto* smallFont = rm.LoadFont("Lingua.otf", 30).get();

	auto* gameOverObj = m_WorkingScene->CreateGameObject();
	gameOverObj->AddComponent<dae::TextComponent>("Game Over", bigFont);

	auto* scoreObj = m_WorkingScene->CreateGameObject();
	scoreObj->AddComponent<dae::TextComponent>("Score: " + std::to_string(m_Score), midFont);

	auto* returnObj = m_WorkingScene->CreateGameObject();
	returnObj->AddComponent<dae::TextComponent>("Press B or ESC to return to the main menu", smallFont);
}

void GameStateComponent::LoadMainMenu()
{
	m_WorkingScene->RemoveAll();
	auto& inputMan = dae::InputManager::GetInstance();
	inputMan.UnbindAll();
	inputMan.RemoveAllGamepads();

	m_MenuChoice = 0;

	auto* cursor = m_WorkingScene->CreateGameObject();
	cursor->AddComponent<dae::TextureComponent>("QbertCurse.png");
	cursor->SetLocalPosition({ 240, 200, 0 });

	auto moveFwdCmd = std::make_unique<SelectMenuCmd>(this, cursor, false);
	auto moveBckCmd = std::make_unique<SelectMenuCmd>(this, cursor, true);
	auto moveFwdCmdKb = std::make_unique<SelectMenuCmd>(this, cursor, false);
	auto moveBckCmdKb = std::make_unique<SelectMenuCmd>(this, cursor, true);

	auto confirmCmd = std::make_unique<ConfirmChoice>(this);
	auto confirmCmdKb = std::make_unique<ConfirmChoice>(this);

	inputMan.AddGamepad();
	inputMan.BindCommand(std::move(moveFwdCmd), GamepadButton::DpadDown, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(moveBckCmd), GamepadButton::DpadUp, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(confirmCmd), GamepadButton::AButton, ButtonState::Pressed, 0);
	
	inputMan.BindCommand(std::move(moveFwdCmdKb), SDL_SCANCODE_DOWN, ButtonState::Pressed);
	inputMan.BindCommand(std::move(moveBckCmdKb), SDL_SCANCODE_UP, ButtonState::Pressed);
	inputMan.BindCommand(std::move(confirmCmdKb), SDL_SCANCODE_RETURN, ButtonState::Pressed);
	

	auto& rm = dae::ResourceManager::GetInstance();
	auto* font = rm.LoadFont("Lingua.otf", 40).get();

	auto* sp = m_WorkingScene->CreateGameObject();
	sp->AddComponent<dae::TextComponent>("Single player", font);
	glm::vec3 topPos = { 300, 200, 0 };
	sp->SetLocalPosition(topPos);

	auto* coop = m_WorkingScene->CreateGameObject();
	coop->AddComponent<dae::TextComponent>("Co-op", font);
	glm::vec3 midPos = { 300, 280, 0 };
	coop->SetLocalPosition(midPos);

	auto* versus = m_WorkingScene->CreateGameObject();
	versus->AddComponent<dae::TextComponent>("Versus", font);
	glm::vec3 bottomPos = { 300, 360, 0 };
	versus->SetLocalPosition(bottomPos);
}

void GameStateComponent::LoadSinglePlayer()
{
	m_WorkingScene->RemoveAll();
	auto& inputMan = dae::InputManager::GetInstance();
	inputMan.UnbindAll();
	inputMan.RemoveAllGamepads();

	inputMan.AddGamepad();

	auto* levelObj = m_WorkingScene->CreateGameObject();
	auto* levelComp = levelObj->AddComponent<LevelComponent>(m_WorkingScene, 0);
	levelObj->SetLocalPosition({ 96, 450, 0 });
	
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	
	auto* scoreObj = m_WorkingScene->CreateGameObject();
	auto* scoreComp = scoreObj->AddComponent<ScoreComponent>(scoreObj->AddComponent<dae::TextComponent>("Score: 0", font.get()));
	
	auto* livesObj = m_WorkingScene->CreateGameObject();
	auto* healthComp = livesObj->AddComponent<HealthComponent>(livesObj->AddComponent<dae::TextComponent>("Lives: 3", font.get()));
	
	auto* uiObj = m_WorkingScene->CreateGameObject();
	scoreObj->SetParent(uiObj, false);
	livesObj->SetParent(uiObj, false);
	livesObj->SetLocalPosition({ 0.f, 30.f, 0 });
	
	auto qbertObj = m_WorkingScene->CreateGameObject();
	auto spriteComp = qbertObj->AddComponent<dae::MultiSpriteComponent>("QBertSpritesheet.png", 1, 4);
	auto qbertComp = qbertObj->AddComponent<QBertComponent>(levelComp, spriteComp);
	levelComp->SetupPlayer(qbertComp, LevelComponent::SpawnPos::Top);
	
	levelComp->AddObserver(qbertComp);
	levelComp->AddObserver(scoreComp);
	qbertComp->AddObserver(healthComp);

	//gamepad commands
	auto leftUpCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, -1 });
	auto rightUpCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 1, 0 });
	auto leftDownCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ -1, 0 });
	auto rightDownCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, 1 });
	
	//keyboard  commands
	auto leftUpCmdKb = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, -1 });
	auto rightUpCmdKb = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 1, 0 });
	auto leftDownCmdKb = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ -1, 0 });
	auto rightDownCmdKb = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, 1 });

	//gamepad binds
	inputMan.BindCommand(std::move(leftUpCmd), GamepadButton::DpadLeft, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(rightUpCmd), GamepadButton::DpadUp, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(leftDownCmd), GamepadButton::DpadDown, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(rightDownCmd), GamepadButton::DpadRight, ButtonState::Pressed, 0);
	
	//keyboard binds
	inputMan.BindCommand(std::move(leftUpCmdKb), SDL_SCANCODE_LEFT, ButtonState::Pressed);
	inputMan.BindCommand(std::move(rightUpCmdKb), SDL_SCANCODE_UP, ButtonState::Pressed);
	inputMan.BindCommand(std::move(leftDownCmdKb), SDL_SCANCODE_DOWN, ButtonState::Pressed);
	inputMan.BindCommand(std::move(rightDownCmdKb), SDL_SCANCODE_RIGHT, ButtonState::Pressed);

	//mute command and bind
	auto toggleMuteCmd = std::make_unique<ToggleMuteCommand>();
	inputMan.BindCommand(std::move(toggleMuteCmd), SDL_SCANCODE_F2, ButtonState::Pressed);

	//skip level command and bind
	auto skipLevelCmd = std::make_unique<SkipLevelCommand>(levelComp, qbertComp);
	inputMan.BindCommand(std::move(skipLevelCmd), SDL_SCANCODE_F4, ButtonState::Pressed);
}
