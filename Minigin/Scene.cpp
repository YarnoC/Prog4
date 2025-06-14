#include "Scene.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) :
	m_name(name)
{
	m_SceneIndex = m_idCounter;
	++m_idCounter;
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject>& object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject>& object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	if (m_objects.empty()) return;
	m_objects.clear();
}

GameObject* dae::Scene::CreateGameObject()
{
	return m_objects.emplace_back(std::make_unique<dae::GameObject>()).get();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::SetActive(bool active)
{
	m_IsActive = active;
}

bool dae::Scene::IsActive() const
{
	return m_IsActive;
}

int dae::Scene::GetIndex() const
{
	return m_SceneIndex;
}

void dae::Scene::RemoveTerminalObjects()
{
	std::erase_if(m_objects, [](std::unique_ptr<dae::GameObject>& obj)
		{
			return obj->IsTerminal();
		});
}

