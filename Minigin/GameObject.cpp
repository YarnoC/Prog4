#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"

dae::Transform dae::GameObject::GetTranform() const
{
	return m_Transform;
}

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

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
