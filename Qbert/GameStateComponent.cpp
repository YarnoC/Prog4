#include "GameStateComponent.h"
#include "Scene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "GameCommands.h"
#include "Inputs.h"
#include "TextureComponent.h"

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
			//load single player;
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
	glm::vec3 pos{ 250, 0, 0 };
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
	//m_WorkingScene->RemoveAll();
	auto& inputMan = dae::InputManager::GetInstance();
	inputMan.UnbindAll();
	inputMan.RemoveAllGamepads();

	m_MenuChoice = 0;

	auto* cursor = m_WorkingScene->CreateGameObject();
	cursor->AddComponent<dae::TextureComponent>("QbertCurse.png");

	auto moveFwdCmd = std::make_unique<SelectMenuCmd>(this, cursor, false);
	auto moveBckCmd = std::make_unique<SelectMenuCmd>(this, cursor, true);
	auto moveFwdCmdKb = std::make_unique<SelectMenuCmd>(this, cursor, false);
	auto moveBckCmdKb = std::make_unique<SelectMenuCmd>(this, cursor, true);

	auto confirmCmd = std::make_unique<ConfirmChoice>(this);
	auto confirmCmdKb = std::make_unique<ConfirmChoice>(this);

	inputMan.AddGamepad();
	inputMan.BindCommand(std::move(moveFwdCmd), GamepadButton::DpadDown, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(moveBckCmd), GamepadButton::DpadUp, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(confirmCmd), GamepadButton::XButton, ButtonState::Pressed, 0);
	
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
