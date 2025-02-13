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
	//TODO: make this not shit and work with a render component of which everything that needs to be rendered can inherit cause this sucks
	//const auto& pos = m_transform.GetPosition();
	for (auto&& comp : m_ComponentVec) //universal ref
	{
		auto renderPtr = dynamic_cast<TextComponent*>(comp.get());

		if (renderPtr)
		{
			renderPtr->Render();
		}
	}
	//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	//m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
