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

void load()
{
	dae::ServiceLocator::RegisterSoundSytem(std::make_unique<dae::SoundSystemSdl>());

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//moved
	//auto levelObj = std::make_unique<dae::GameObject>();
	auto levelObj = scene.CreateGameObject();
	auto levelComp = levelObj->AddComponent<LevelComponent>(&scene, 0);
	levelObj->SetLocalPosition({ 96, 450, 0 });
	//scene.Add(levelObj);

	//background
	//go->AddComponent<dae::TextureComponent>("background.tga");
	//scene.Add(go);

	//logo
	//go = std::make_unique<dae::GameObject>();
	//go->AddComponent<dae::TextureComponent>("logo.tga");
	//go->SetLocalPosition({ 216, 180, 0 });
	//scene.Add(go);


	//auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	//auto textObject = std::make_unique<dae::GameObject>();
	//textObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font.get());
	//textObject->SetLocalPosition({ 100, 20, 0 });
	//scene.Add(textObject);


	//auto&& ss = dae::ServiceLocator::GetSoundSystem();
	
	//auto jumpWav = ss.LoadEffect("Sounds/QBertJump.ogg");
	//ss.Play(jumpWav, 10, true);

	//actual objects

	auto qbertObj = scene.CreateGameObject();
	auto spriteComp = qbertObj->AddComponent<dae::MultiSpriteComponent>("QBertSpritesheet.png", 1, 4);
	auto qbertComp = qbertObj->AddComponent<QBertComponent>(levelComp, spriteComp);
	levelComp->SetupPlayer(qbertComp, LevelComponent::SpawnPos::Top);

	//auto qbertObj2 = scene.CreateGameObject();
	//qbertObj2->SetLocalPosition({ 100, 400, 0 });
	//qbertObj2->AddComponent<dae::TextureComponent>("QBertSpritesheet.png");

	//gamepad commands
	//auto leftCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ -100.f, 0.f });
	//auto rightCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 100.f, 0.f });
	//auto upCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 0.f, -100.f });
	//auto downCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 0.f, 100.f });

	auto leftUpCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, -1 });
	auto rightUpCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 1, 0 });
	auto leftDownCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ -1, 0 });
	auto rightDownCmd = std::make_unique<MoveQBertCommand>(qbertComp, glm::ivec2{ 0, 1 });

	//keyboard  commands
	//auto leftCmdKb = std::make_unique<MoveActorCommand>(qbertObj2, glm::vec2{ -150.f, 0.f });
	//auto rightCmdKb = std::make_unique<MoveActorCommand>(qbertObj2, glm::vec2{ 150.f, 0.f });
	//auto upCmdKb = std::make_unique<MoveActorCommand>(qbertObj2, glm::vec2{ 0.f, -150.f });
	//auto downCmdKb = std::make_unique<MoveActorCommand>(qbertObj2, glm::vec2{ 0.f, 150.f });

	auto& inputMan = dae::InputManager::GetInstance();

	//gamepad binds
	inputMan.AddGamepad();
	//inputMan.BindCommand(std::move(leftCmd), GamepadButton::DpadLeft, ButtonState::Held, 0);
	//inputMan.BindCommand(std::move(rightCmd), GamepadButton::DpadRight, ButtonState::Held, 0);
	//inputMan.BindCommand(std::move(upCmd), GamepadButton::DpadUp, ButtonState::Held, 0);
	//inputMan.BindCommand(std::move(downCmd), GamepadButton::DpadDown, ButtonState::Held, 0);

	inputMan.BindCommand(std::move(leftUpCmd), GamepadButton::DpadLeft, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(rightUpCmd), GamepadButton::DpadUp, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(leftDownCmd), GamepadButton::DpadDown, ButtonState::Pressed, 0);
	inputMan.BindCommand(std::move(rightDownCmd), GamepadButton::DpadRight, ButtonState::Pressed, 0);

	//keyboard binds
	//inputMan.BindCommand(std::move(leftCmdKb), SDL_SCANCODE_LEFT, ButtonState::Held);
	//inputMan.BindCommand(std::move(rightCmdKb), SDL_SCANCODE_RIGHT, ButtonState::Held);
	//inputMan.BindCommand(std::move(upCmdKb), SDL_SCANCODE_UP, ButtonState::Held);
	//inputMan.BindCommand(std::move(downCmdKb), SDL_SCANCODE_DOWN, ButtonState::Held);

	//mute command and bind
	auto toggleMuteCmd = std::make_unique<ToggleMuteCommand>();
	inputMan.BindCommand(std::move(toggleMuteCmd), SDL_SCANCODE_F2, ButtonState::Pressed);

	auto skipLevelCmd = std::make_unique<SkipLevelCommand>(levelComp, qbertComp);
	inputMan.BindCommand(std::move(skipLevelCmd), SDL_SCANCODE_F4, ButtonState::Pressed);

	//auto go = std::make_unique<dae::GameObject>();
	//go = std::make_unique<dae::GameObject>();
	//go->SetLocalPosition({ 20, 20, 0 });
	//go->AddComponent<dae::TextComponent>(" ", font.get());
	//go->AddComponent<FpsComponent>(go->GetComponent<dae::TextComponent>());
	//scene.Add(go);
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}