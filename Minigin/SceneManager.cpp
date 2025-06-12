#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		if (!scene->IsActive()) continue;

		scene->Update();
	}
}

void dae::SceneManager::LateUpdate()
{
	for (const auto& scene : m_scenes)
	{
		if (!scene->IsActive()) continue;

		scene->RemoveTerminalObjects();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		if (!scene->IsActive()) continue;

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

void dae::SceneManager::RemoveScene(int index)
{
	m_scenes.erase(m_scenes.begin() + index);
}

void dae::SceneManager::SetSceneActive(int index, bool active)
{
	m_scenes[index]->SetActive(active);
}
