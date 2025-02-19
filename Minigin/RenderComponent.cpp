#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

void RenderComponent::Render() const
{
	for (const auto& comp : m_RenderVec)
	{
		//const auto& pos = comp->GetOwner()->GetTranform();
		const auto& pos = comp->GetOwner()->GetTranform().GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*(comp->GetTexturePtr()), pos.x, pos.y);
	}
}

RenderComponent::RenderComponent(dae::GameObject* ownerPtr) : Component(ownerPtr)
{
}

//void TextureComponent::Render() const
//{
//	const auto& pos = m_OwnerPtr->GetTranform().GetPosition();
//	dae::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
//}