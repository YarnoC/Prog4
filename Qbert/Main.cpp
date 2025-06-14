#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "GameCommands.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "SoundSystemSdl.h"
#include "MultiSpriteComponent.h"
#include "LevelComponent.h"
#include "QBertComponent.h"
#include "ScoreComponent.h"

void load()
{
	dae::ServiceLocator::RegisterSoundSytem(std::make_unique<dae::SoundSystemSdl>());

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto* levelObj = scene.CreateGameObject();
	auto* levelComp = levelObj->AddComponent<LevelComponent>(&scene, 0);
	levelObj->SetLocalPosition({ 96, 450, 0 });

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);

	auto* scoreObj = scene.CreateGameObject();
	auto* scoreComp = scoreObj->AddComponent<ScoreComponent>(scoreObj->AddComponent<dae::TextComponent>("Score: 0", font.get()));

	//go->AddComponent<dae::TextureComponent>("background.tga");

	//textObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font.get());

	auto qbertObj = scene.CreateGameObject();
	auto spriteComp = qbertObj->AddComponent<dae::MultiSpriteComponent>("QBertSpritesheet.png", 1, 4);
	auto qbertComp = qbertObj->AddComponent<QBertComponent>(levelComp, spriteComp);
	levelComp->SetupPlayer(qbertComp, LevelComponent::SpawnPos::Top);

	levelComp->AddObserver(qbertComp);
	levelComp->AddObserver(scoreComp);

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

	auto& inputMan = dae::InputManager::GetInstance();

	//gamepad binds
	inputMan.AddGamepad();

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

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}