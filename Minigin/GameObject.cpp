#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (auto&& comp : m_ComponentVec)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto&& comp : m_ComponentVec) //universal ref
	{
		auto renderPtr = dynamic_cast<Renderable*>(comp.get());

		if (renderPtr)
		{
			renderPtr->Render();
		}
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	//m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
