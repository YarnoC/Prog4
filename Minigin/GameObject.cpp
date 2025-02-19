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

//TODO: make awake so this can be const again
void dae::GameObject::Render()
{
	//should maybe make an awake so i can do the stuff there
	if (m_RenderComponent == nullptr)
	{
		m_RenderComponent = GetComponent<RenderComponent>();
	}

	if (m_RenderComponent == nullptr) return;

	m_RenderComponent->Render();

	//for (auto&& comp : m_ComponentVec) //universal ref
	//{
	//	auto renderPtr = dynamic_cast<Renderable*>(comp.get());
	//
	//	if (renderPtr)
	//	{
	//		renderPtr->Render();
	//	}
	//}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
