#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

void RenderComponent::Render() const
{
	if (m_LinkedTexture == nullptr) return; //HACK: ask about optimizing the linking

	const auto& pos = GetOwner()->GetTranform().GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_LinkedTexture, pos.x, pos.y);
}

void RenderComponent::LinkTexture(dae::Texture2D* texture)
{
	m_LinkedTexture = texture;
}

RenderComponent::RenderComponent(dae::GameObject* ownerPtr) : Component(ownerPtr), m_LinkedTexture{nullptr}
{
}