#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		scene->RemoveTerminalObjects();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

//need to be declared here because else the unique pointer complains that it can't delete imcomplete type
dae::SceneManager::SceneManager() = default;

dae::SceneManager::~SceneManager() = default;

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	//can't use make_unique here as that function doesn't have access to the private ctor of scene
	auto scene = std::move(std::unique_ptr<Scene>(new Scene(name)));
	m_scenes.push_back(std::move(scene));
	return *m_scenes.back();
}
