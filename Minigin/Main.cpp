#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
//#include "TextObject.h"
#include "Scene.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"

#include "Command.h"
#include "Inputs.h"
#include "InputManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

	//logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextureComponent>("logo.tga");
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(go);

	//TODO: this returns a shared_ptr, change this to raw, maybe not need to ask about something here
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);

	auto textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<TextComponent>("Programming 4 Assignment", font.get());
	textObject->SetLocalPosition({ 100, 20, 0 });

	scene.Add(textObject);

	//actual objects

	auto qbertObj = std::make_unique<dae::GameObject>();
	qbertObj->SetLocalPosition({ 100, 300, 0 });
	qbertObj->AddComponent<TextureComponent>("QBert.png");
	auto leftCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{-20.f, 0.f});
	auto rightCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{20.f, 0.f});
	auto upCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{0.f, -20.f});
	auto downCmd = std::make_unique<MoveActorCommand>(qbertObj.get(), glm::vec2{0.f, 20.f});

	//ran into issues binding the controls :(

	//auto& inputMan = dae::InputManager::GetInstance();
	//inputMan.RegisterCommand(InputButton::DpadLeft, leftCmd);

	auto qbertObj2 = std::make_unique<dae::GameObject>();
	qbertObj2->SetLocalPosition({ 100, 400, 0 });
	qbertObj2->AddComponent<TextureComponent>("QBert.png");
	
	scene.Add(qbertObj);
	scene.Add(qbertObj2);

	go = std::make_unique<dae::GameObject>();
	go->SetPosition(20, 20);
	go->AddComponent<TextComponent>(" ", font.get());
	go->AddComponent<FpsComponent>(go->GetComponent<TextComponent>());
	scene.Add(go);

	
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
