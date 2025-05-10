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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(go);

	//logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.tga");
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(go);

	//TODO: this returns a shared_ptr, change this to raw, maybe not need to ask about something here
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);

	auto textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font.get());
	textObject->SetLocalPosition({ 100, 20, 0 });

	scene.Add(textObject);

	dae::ServiceLocator::RegisterSoundSytem(std::make_unique<dae::SoundSystemSdl>());
	auto&& ss = dae::ServiceLocator::GetSoundSystem();
	
	auto jumpWav = ss.LoadEffect("../Data/Sounds/QBertJump.wav");
	ss.Play(jumpWav, 10, true);

	//actual objects

	auto qbertObj = std::make_unique<dae::GameObject>();
	qbertObj->SetLocalPosition({ 100, 300, 0 });
	qbertObj->AddComponent<dae::TextureComponent>("QBert.png");

	auto qbertObj2 = std::make_unique<dae::GameObject>();
	qbertObj2->SetLocalPosition({ 100, 400, 0 });
	qbertObj2->AddComponent<dae::TextureComponent>("QBert.png");

	//gamepad commands
	auto leftCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ -100.f, 0.f });
	auto rightCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 100.f, 0.f });
	auto upCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 0.f, -100.f });
	auto downCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{ 0.f, 100.f });

	//keyboard  commands
	auto leftCmdKb = std::make_unique<MoveActorCommand>(qbertObj2.get(), glm::vec2{ -150.f, 0.f });
	auto rightCmdKb = std::make_unique<MoveActorCommand>(qbertObj2.get(), glm::vec2{ 150.f, 0.f });
	auto upCmdKb = std::make_unique<MoveActorCommand>(qbertObj2.get(), glm::vec2{ 0.f, -150.f });
	auto downCmdKb = std::make_unique<MoveActorCommand>(qbertObj2.get(), glm::vec2{ 0.f, 150.f });

	auto& inputMan = dae::InputManager::GetInstance();

	//gamepad binds
	inputMan.AddGamepad();
	inputMan.BindCommand(std::move(leftCmd), GamepadButton::DpadLeft, ButtonState::Held, 0);
	inputMan.BindCommand(std::move(rightCmd), GamepadButton::DpadRight, ButtonState::Held, 0);
	inputMan.BindCommand(std::move(upCmd), GamepadButton::DpadUp, ButtonState::Held, 0);
	inputMan.BindCommand(std::move(downCmd), GamepadButton::DpadDown, ButtonState::Held, 0);

	//keyboard binds
	inputMan.BindCommand(std::move(leftCmdKb), SDL_SCANCODE_LEFT, ButtonState::Held);
	inputMan.BindCommand(std::move(rightCmdKb), SDL_SCANCODE_RIGHT, ButtonState::Held);
	inputMan.BindCommand(std::move(upCmdKb), SDL_SCANCODE_UP, ButtonState::Held);
	inputMan.BindCommand(std::move(downCmdKb), SDL_SCANCODE_DOWN, ButtonState::Held);

	scene.Add(qbertObj);
	scene.Add(qbertObj2);

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(20, 20);
	go->AddComponent<dae::TextComponent>(" ", font.get());
	go->AddComponent<FpsComponent>(go->GetComponent<dae::TextComponent>());
	scene.Add(go);
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}