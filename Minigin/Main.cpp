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
#include "RenderComponent.h"
#include "RotatorComponent.h"

#include "CacheBenchmark.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	go->AddComponent<TextureComponent>("background.tga");
	auto rend = go->GetComponent<RenderComponent>();
	auto txPtr = go->GetComponent<TextureComponent>()->GetTexturePtr();
	rend->LinkTexture(txPtr);
	scene.Add(go);

	//logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextureComponent>("logo.tga");
	go->SetLocalPosition({ 216, 180, 0 });
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->LinkTexture(go->GetComponent<TextureComponent>()->GetTexturePtr());
	scene.Add(go);

	//TODO: this returns a shared_ptr, change this to raw, maybe not need to ask about something here
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);

	auto textObject = std::make_unique<dae::GameObject>();
	textObject->AddComponent<TextComponent>("Programming 4 Assignment", font.get());
	textObject->SetLocalPosition({ 100, 20, 0 });
	textObject->AddComponent<RenderComponent>();
	textObject->GetComponent<RenderComponent>()->LinkTexture(textObject->GetComponent<TextComponent>()->GetTexturePtr());

	scene.Add(textObject);

	//Trash the Cache
	CacheBenchmark cacheTest{};

	cacheTest.TimeInts();
	cacheTest.TimeGo();
	cacheTest.TimeGoa();

	//TODO: FIX, currently broken, will fix later but first the scenegraph
	/*

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<FpsComponent>();
	go->AddComponent<TextComponent>(" ", font.get());
	go->SetPosition(20, 20);
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->LinkTexture(go->GetComponent<TextComponent>()->GetTexturePtr());
	scene.Add(go);

	*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}
